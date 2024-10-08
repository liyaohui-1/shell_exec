#!/bin/bash

read -t 30 -p "Please input your name: " name
#提示“请输入姓名”并等待30 秒，把用户的输入保存入变量name 中
echo "Name is $name"
#看看变量“$name”中是否保存了你的输入

read -s -t 30 -p "Please enter your age: " age
#提示“请输入年龄”并等待30秒，把用户的输入保存入变量age中
#年龄是隐私，所以我们用“-s”选项隐藏输入
echo -e "\n"
#调整输出格式，如果不输出换行，一会的年龄输出不会换行
echo "Age is $age"

read -n 1 -t 30 -p "Please select your gender[M/F]:" gender
#提示“请选择性别”并等待30秒，把用户的输入保存入变量gender
#使用“-n1”选项只接收一个输入字符就会执行（都不用输入回车）
echo -e "\n"
echo "Sex is $gender"
