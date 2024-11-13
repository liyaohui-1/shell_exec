//
//  多线程版Hello World服务
//
#include "zhelpers.h"
#include <pthread.h>
#include <unistd.h>

static void* worker_routine(void* context)
{
    //  连接至代理的套接字
    void* receiver = zmq_socket(context, ZMQ_REP);
    zmq_connect(receiver, "inproc://workers");

    while (1) {
        char* string = s_recv(receiver);
        printf("Received request: [%s]\n", string);
        free(string);
        //  工作
        sleep(1);
        //  返回应答
        s_send(receiver, "World");
    }
    zmq_close(receiver);
    return NULL;
}

int main(void)
{
    void* context = zmq_ctx_new();

    //  用于和client进行通信的套接字
    void* clients = zmq_socket(context, ZMQ_ROUTER);
    zmq_bind(clients, "tcp://*:5555");

    //  用于和worker进行通信的套接字
    void* workers = zmq_socket(context, ZMQ_DEALER);
    zmq_bind(workers, "inproc://workers");

    //  启动一个worker池
    int thread_nbr;
    for (thread_nbr = 0; thread_nbr < 5; thread_nbr++) {
        pthread_t worker;
        pthread_create(&worker, NULL, worker_routine, context);
    }
    //  启动队列装置
    zmq_device(ZMQ_QUEUE, clients, workers);

    //  程序不会运行到这里，但仍进行清理工作
    zmq_close(clients);
    zmq_close(workers);
    zmq_ctx_destroy(context);
    return 0;
}

/*
    服务端启动一组worker线程，每个worker创建一个REP套接字，并处理收到的请求。worker线程就像是一个单线程的服务，唯一的区别是使用了inproc而非tcp协议，以及绑定-连接的方向调换了。
    服务端创建ROUTER套接字用以和client通信，因此提供了一个TCP协议的外部接口。
    服务端创建DEALER套接字用以和worker通信，使用了内部接口（inproc）。
    服务端启动了QUEUE内部装置，连接两个端点上的套接字。QUEUE装置会将收到的请求分发给连接上的worker，并将应答路由给请求方。

    示例中的“工作”仅仅是1秒钟的停留，我们可以在worker中进行任意的操作，包括与其他节点进行通信。消息的流向是这样的：REQ-ROUTER-queue-DEALER-REP。
*/