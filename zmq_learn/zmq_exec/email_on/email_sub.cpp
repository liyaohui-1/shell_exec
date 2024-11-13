#include "zhelpers.h"

int main(void)
{
    //  准备上下文和SUB套接字
    void* context = zmq_init(1);
    void* subscriber = zmq_socket(context, ZMQ_SUB);
    zmq_connect(subscriber, "tcp://localhost:5563");
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "B", 1);

    while (1) {
        //  读取消息信封
        char* address = s_recv(subscriber);
        //  读取消息内容
        char* contents = s_recv(subscriber);
        printf("[%s] %s\n", address, contents);
        free(address);
        free(contents);
    }
    //  正确退出
    zmq_close(subscriber);
    zmq_term(context);
    return 0;
}