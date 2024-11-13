//
//  任务收集器
//  绑定PULL套接字至tcp://localhost:5558端点
//  从worker处收集处理结果
//
#include "zhelpers.h"

int main(void)
{
    //  准备上下文和套接字
    void* context = zmq_ctx_new();
    void* receiver = zmq_socket(context, ZMQ_PULL);
    zmq_bind(receiver, "tcp://*:5558");

    //  等待开始信号
    char* string = s_recv(receiver);
    free(string);

    //  开始计时
    int64_t start_time = s_clock();

    //  确定100个任务均已处理
    int task_nbr;
    for (task_nbr = 0; task_nbr < 100; task_nbr++) {
        char* string = s_recv(receiver);
        free(string);
        if ((task_nbr / 10) * 10 == task_nbr)
            printf(":");
        else
            printf(".");
        fflush(stdout);
    }
    //  计算并输出总执行时间
    printf("执行时间: %d 毫秒\n", (int)(s_clock() - start_time));

    zmq_close(receiver);
    zmq_ctx_destroy(context);
    return 0;
}