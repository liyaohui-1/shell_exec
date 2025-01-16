#!/bin/bash
# mytest为进程名
while true; do
    PID=$(ps -ef|grep -v grep|grep "mytest" |awk '{print $2}')
    # 检查进程是否存在

    if [ -z "$PID" ]; then
        # 进程不存在，启动进程
        echo "mytest Notebook is not running. Starting it..."
        # 这里替换为你启动进程的命令
        /home/lyh/My/shell_exec/check_and_restart/start.sh &
    else
        # 进程存在，输出进程ID
        # echo -e "mytest Notebook is running with PID: \n${PID}"
        echo "mytest Notebook is running with PID: ${PID}"
    fi
    sleep 1
    echo "1s later..."
done

