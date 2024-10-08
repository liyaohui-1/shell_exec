#!/bin/bash

#统计根分区使用率
rate=$(df -h | grep "dev/sda1" | awk '{print $5}' | cut -d "%" -f1)
#把根分区使用率作为变量值赋予变量rate
if [ $rate -ge 80 ]
    then
        echo 'Warning!/dev/sda1 is full!!'
    else
        echo "/dev/sda1 is $rate%."
fi