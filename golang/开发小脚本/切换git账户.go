package main

import (
	"flag"
	"fmt"
	"os"
	"os/exec"
)

const (
	pri       = "pri"
	priName   = "fnq9999"
	priEmail  = "1411728428@qq.com"
	work      = "work"
	workEmail = "funianqin@bytedance.com"
	workName  = "funianqin"
)

func main() {
	//var input string
	input := flag.String("u", work, "默认是工作状态")
	flag.Parse()
	if *input == work {
		fmt.Printf("NAME %s\n EMAIL:%s\n", workName, workEmail)
		cmd := exec.Command("git", "config", "--global", "user.name", workName)
		cmd.Stdout = os.Stdout
		_ = cmd.Run()
		cmd = exec.Command("git", "config", "--global", "user.email", workEmail)
		cmd.Stdout = os.Stdout
		_ = cmd.Run()
		return
	}
	fmt.Printf("NAME %s\n EMAIL:%s\n", priName, priEmail)
	cmd := exec.Command("git", "config", "--global", "user.name", priName)
	cmd.Stdout = os.Stdout
	_ = cmd.Run()
	cmd = exec.Command("git", "config", "--global", "user.email", priEmail)
	cmd.Stdout = os.Stdout
	_ = cmd.Run()
}
