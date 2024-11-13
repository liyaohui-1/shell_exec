//
// 多线程同步
//
#include "zhelpers.h"
#include <pthread.h>

static void* step1(void* context)
{
    //  连接至步骤2，告知我已就绪
    void* xmitter = zmq_socket(context, ZMQ_PAIR);
    zmq_connect(xmitter, "inproc://step2");
    printf("步骤1就绪，正在通知步骤2……\n");
    s_send(xmitter, "READY");
    zmq_close(xmitter);

    return NULL;
}

static void* step2(void* context)
{
    //  启动步骤1前线绑定至inproc套接字
    void* receiver = zmq_socket(context, ZMQ_PAIR);
    zmq_bind(receiver, "inproc://step2");
    pthread_t thread;
    pthread_create(&thread, NULL, step1, context);

    //  等待信号
    char* string = s_recv(receiver);
    free(string);
    zmq_close(receiver);

    //  连接至步骤3，告知我已就绪
    void* xmitter = zmq_socket(context, ZMQ_PAIR);
    zmq_connect(xmitter, "inproc://step3");
    printf("步骤2就绪,正在通知步骤3……\n");
    s_send(xmitter, "READY");
    zmq_close(xmitter);

    return NULL;
}

int main(void)
{
    void* context = zmq_ctx_new();

    //  启动步骤2前线绑定至inproc套接字
    void* receiver = zmq_socket(context, ZMQ_PAIR);
    zmq_bind(receiver, "inproc://step3");
    pthread_t thread;
    pthread_create(&thread, NULL, step2, context);

    //  等待信号
    char* string = s_recv(receiver);
    free(string);
    zmq_close(receiver);

    printf("测试成功！\n");
    zmq_ctx_destroy(context);
    return 0;
}