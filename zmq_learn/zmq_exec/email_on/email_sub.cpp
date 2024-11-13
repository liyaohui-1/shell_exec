#include "zhelpers.h"

int main(void)
{
    //  准备上下文和SUB套接字
    void* context = zmq_ctx_new();
    void* subscriber = zmq_socket(context, ZMQ_SUB);
    zmq_connect(subscriber, "tcp://localhost:5563");
    // 选择订阅，此时仅订阅"信封"为B的消息
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
    zmq_ctx_destroy(context);
    return 0;
}