//
//  任务分发器
//  绑定PUSH套接字至tcp://localhost:5557端点
//  发送一组任务给已建立连接的worker
//
#include "zhelpers.h"
#include <unistd.h>

int main(void)
{
    void* context = zmq_init(1);

    //  用于发送消息的套接字
    void* sender = zmq_socket(context, ZMQ_PUSH);
    zmq_bind(sender, "tcp://*:5557");

    //  用于发送开始信号的套接字
    void* sink = zmq_socket(context, ZMQ_PUSH);
    zmq_connect(sink, "tcp://localhost:5558");

    printf("准备好worker后按任意键开始: ");
    getchar();
    printf("正在向worker分配任务...\n");

    //  发送开始信号
    s_send(sink, "0");

    //  初始化随机数生成器
    srandom((unsigned)time(NULL));

    //  发送100个任务
    int task_nbr;
    int total_msec = 0; //  预计执行时间（毫秒）
    for (task_nbr = 0; task_nbr < 100; task_nbr++) {
        int workload;
        //  随机产生1-100毫秒的工作量
        workload = randof(100) + 1;
        total_msec += workload;
        char string[10];
        sprintf(string, "%d", workload);
        s_send(sender, string);
    }
    printf("预计执行时间: %d 毫秒\n", total_msec);
    sleep(1); //  延迟一段时间，让任务分发完成

    zmq_close(sink);
    zmq_close(sender);
    zmq_term(context);
    return 0;
}