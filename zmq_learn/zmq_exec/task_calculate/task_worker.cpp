//
//  任务执行器
//  连接PULL套接字至tcp://localhost:5557端点
//  从任务分发器处获取任务
//  连接PUSH套接字至tcp://localhost:5558端点
//  向结果采集器发送结果
//
#include "zhelpers.h"

int main(void)
{
    void* context = zmq_ctx_new();

    //  获取任务的套接字
    void* receiver = zmq_socket(context, ZMQ_PULL);
    zmq_connect(receiver, "tcp://localhost:5557");

    //  发送结果的套接字
    void* sender = zmq_socket(context, ZMQ_PUSH);
    zmq_connect(sender, "tcp://localhost:5558");

    //  循环处理任务
    while (1) {
        char* string = s_recv(receiver);
        //  输出处理进度
        fflush(stdout);
        printf("%s.", string);

        //  开始处理
        s_sleep(atoi(string));
        free(string);

        //  发送结果
        s_send(sender, "");
    }
    zmq_close(receiver);
    zmq_close(sender);
    zmq_ctx_destroy(context);
    return 0;
}