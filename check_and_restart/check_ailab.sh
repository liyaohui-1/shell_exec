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


# 要监控的程序名称列表
# PROGRAMS=("mytest" "another_program")

# while true; do
#     for PROGRAM in "${PROGRAMS[@]}"; do
#         # 获取程序进程ID，排除grep命令本身
#         PID=$(ps -ef | grep "$PROGRAM" | grep -v grep | awk '{print $2}')
        
#         # 检查是否获取到了进程ID（即程序是否在运行）
#         if [ -z "$PID" ]; then
#             # 进程不存在，启动进程
#             echo "$PROGRAM is not running. Starting it..."
#             # 这里替换为启动对应程序的命令
#             # 假设每个程序都有一个对应的启动脚本，路径如下：
#             case "$PROGRAM" in
#                 "mytest")
#                     /home/lyh/My/shell_exec/check_and_restart/start_mytest.sh &
#                     ;;
#                 "another_program")
#                     /home/lyh/My/shell_exec/check_and_restart/start_another_program.sh &
#                     ;;
#                 # 可以根据需要添加更多程序及其启动脚本
#             esac
#         else
#             # 进程存在，输出进程ID（可选）
#             echo "$PROGRAM is running with PID: $PID"
#         fi
#     done
    
#     # 等待一段时间后再次检查
#     sleep 1
#     echo "1s later, checking again..."
# done

