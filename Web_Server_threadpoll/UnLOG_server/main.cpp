#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cassert>
#include <sys/epoll.h>
#include"lst_timer.h"
#include "locker.h"
#include "threadpool.h"
#include "http_conn.cpp"

#define MAX_FD 65536
#define MAX_EVENT_NUMBER 10000
#define TIMESLOT 5
static int pipefd[2];
static sort_timer_lst timer_lst;
static int epollfd=0;
static locker conn_lock;
//int addfd( int epollfd, int fd, bool one_shot );
//int removefd( int epollfd, int fd );
void sig_handler(int sig){///
    int save_errno=errno;
    int msg=sig;
    send(pipefd[1],(char*)&msg,1,0);
    errno =save_errno;
}
void timer_handler(){
    timer_lst.tick();
    alarm(TIMESLOT);
}
void cb_func(client_data* user_data){
    //printf("cu_func\n");
    epoll_ctl(epollfd,EPOLL_CTL_DEL,user_data->sockfd,0);
    assert(user_data);
    close(user_data->sockfd);
    http_conn::m_user_count--;
}
void addsig( int sig, void( handler )(int), bool restart = true )
{
    struct sigaction sa;
    memset( &sa, '\0', sizeof( sa ) );
    sa.sa_handler = handler;
    if( restart )
    {
        sa.sa_flags |= SA_RESTART;
    }
    sigfillset( &sa.sa_mask );
    assert( sigaction( sig, &sa, NULL ) != -1 );
}

void show_error( int connfd, const char* info )
{
    printf( "%s", info );
    send( connfd, info, strlen( info ), 0 );
    close( connfd );
}


int main( int argc, char* argv[] )
{
    if( argc <= 2 )
    {
        printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi( argv[2] );
    addsig( SIGPIPE, SIG_IGN );
    beian_len=strlen(beian_str);
    threadpool< http_conn >* pool = NULL;
    try
    {
        pool = new threadpool< http_conn >;
    }
    catch( ... )
    {
        return 1;
    }

    http_conn* users = new http_conn[ MAX_FD ];
    assert( users );
    int user_count = 0;

    int listenfd = socket( PF_INET, SOCK_STREAM, 0 );

    assert( listenfd >= 0 );
    struct linger tmp = { 1, 0 };
    setsockopt( listenfd, SOL_SOCKET, SO_LINGER, &tmp, sizeof( tmp ) );

    int ret = 0;
    struct sockaddr_in address;
    bzero( &address, sizeof( address ) );
    address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &address.sin_addr );
    address.sin_port = htons( port );
    int flag=1;
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(flag));
    ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
    assert( ret >= 0 );

    ret = listen( listenfd, 5);
    assert( ret >= 0 );

    epoll_event events[ MAX_EVENT_NUMBER ];
    epollfd = epoll_create( 5 );
    assert( epollfd != -1 );

    addfd_listen( epollfd, listenfd, false );


    http_conn::m_epollfd = epollfd;

    /// create pipe
    ret=socketpair(PF_UNIX,SOCK_STREAM,0,pipefd);
    assert(ret!=-1);
    setnonblocking(pipefd[1]);
    addfd(epollfd,pipefd[0],false);

    addsig(SIGALRM,sig_handler,false);
    addsig(SIGTERM,sig_handler,false);
    bool stop_server=false;
    client_data *users_timer=new client_data[MAX_FD];
    bool timeout=false;
    alarm(TIMESLOT);

    while( !stop_server)
    {
        printf("1-----------------------\n");
        int number = epoll_wait( epollfd, events, MAX_EVENT_NUMBER, -1 );
        printf("2-----------------------\n");
        if ( ( number < 0 ) && ( errno != EINTR ) )
        {
            printf( "epoll failure\n" );
            break;
        }

        for ( int i = 0; i < number; i++ )
        {
            printf("3-----------------------\n");
            int sockfd = events[i].data.fd;

            if( sockfd == listenfd )
            {
                printf("4-----------------------\n");
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof( client_address );
                int connfd;
                while(connfd=accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength )){
                        printf("5-----------------------\n");
                    if ( connfd < 0 )
                    {
                        printf( "errno is: %d\n", errno );
                        break;
                    }
                    if( http_conn::m_user_count >= MAX_FD )
                    {
                        show_error( connfd, "Internal server busy" );
                        printf("server_busy\n");
                        close(connfd);
                        continue;
                    }
//                    int client_port=ntohs((client_address.sin_port));
//                    printf("client_port: %d\n",client_port);
                    users[connfd].init( connfd, client_address );
                    users_timer[connfd].address=client_address;
                    users_timer[connfd].sockfd=connfd;
                    util_timer* timer=new util_timer;
                    timer->user_data=&users_timer[connfd];
                    timer->cb_func=cb_func;
                    time_t cur=time(NULL);
                    timer->expire=cur+3*TIMESLOT;
                    users_timer[connfd].timer=timer;
                    timer_lst.add_timer(timer);
                }

//                int connfd=accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength );
//                 if ( connfd < 0 )
//                    {
//                        printf( "errno is: %d\n", errno );
//                        break;
//                    }
//                    if( http_conn::m_user_count >= MAX_FD )
//                    {
//                        show_error( connfd, "Internal server busy" );
//                        printf("server_busy\n");
//                        close(connfd);
//                        continue;
//                    }
//                    int client_port=ntohs((client_address.sin_port));
//                    printf("client_port: %d\n",client_port);
//                    users[connfd].init( connfd, client_address );
//                    users_timer[connfd].address=client_address;
//                    users_timer[connfd].sockfd=connfd;
//                    util_timer* timer=new util_timer;
//                    timer->user_data=&users_timer[connfd];
//                    timer->cb_func=cb_func;
//                    time_t cur=time(NULL);
//                    timer->expire=cur+3*TIMESLOT;
//                    users_timer[connfd].timer=timer;
//                    timer_lst.add_timer(timer);
            }
            else if( events[i].events & (EPOLLRDHUP|EPOLLHUP|EPOLLERR) )
            {
                printf("6-----------------------\n");
                //users[sockfd].close_conn();
                util_timer* timer=users_timer[sockfd].timer;
                timer->cb_func(&users_timer[sockfd]);
                if(timer){
                    timer_lst.del_timer(timer);
                }
            }
            else if ((sockfd==pipefd[0])&&(events[i].events&EPOLLIN)){
                    printf("7-----------------------\n");
                int sig;
                char signals[1024];
                ret=recv(pipefd[0],signals,sizeof(signals),0);
                if(ret==-1){
                    continue;
                }else if(ret==0){
                    continue;
                }
                else{
                    for(int i=0;i<ret;++i){
                        switch(signals[i]){
                            case SIGALRM:{
                                timeout=1;
                                break;
                            }
                            case SIGTERM:{
                                stop_server=true;
                            }
                        }
                    }
                }
            }
            else if( events[i].events & EPOLLIN )
            {
                printf("8-----------------------\n");
                util_timer* timer=users_timer[sockfd].timer;
                if(users[sockfd].read()){
                    pool->append( users + sockfd );
                    if(timer){
                        time_t cur=time(NULL);
                        timer->expire=cur+3*TIMESLOT;
                        timer_lst.adjust_timer(timer);
                    }
                }
                else{
                    //printf("????\n");
                    timer->cb_func(&users_timer[sockfd]);
                    if(timer){
                        timer_lst.del_timer(timer);
                    }
                }
//                if( users[sockfd].read() )
//                {
//                    pool->append( users + sockfd );
//                }
//                else
//                {
//                    printf("read_fail\n");
//                    users[sockfd].close_conn();
//                }
            }
            else if( events[i].events & EPOLLOUT )
            {
                printf("9-----------------------\n");
                util_timer* timer=users_timer[sockfd].timer;
                if(users[sockfd].write()){

                    if(timer){
                        time_t cur=time(NULL);
                        timer->expire=cur+3*TIMESLOT;
                        timer_lst.adjust_timer(timer);
                    }
                }else{
                    timer->cb_func(&users_timer[sockfd]);
                    if(timer){
                        timer_lst.del_timer(timer);
                    }
                }
//                if( !users[sockfd].write() )
//                {
//                    users[sockfd].close_conn();
//                }
            }

//            else
//            {
//               printf("dont know what to do\n");
//                //users[sockfd].close_conn();
//                //modfd()
//            }
        }
        if(timeout){
            timer_handler();
            timeout=false;
        }
    }

    close( epollfd );
    close( listenfd );
    close(pipefd[1]);
    close(pipefd[0]);
    delete [] users;
    delete[]users_timer;
    delete pool;
    return 0;
}
