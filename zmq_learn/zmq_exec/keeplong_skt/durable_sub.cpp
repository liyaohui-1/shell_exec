//
//  持久化的订阅者
//
#include "zhelpers.h"

int main(void)
{
    void* context = zmq_init(1);

    //  连接SUB套接字
    void* subscriber = zmq_socket(context, ZMQ_SUB);
    zmq_setsockopt(subscriber, ZMQ_IDENTITY, "Hello", 5);
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "", 0);
    zmq_connect(subscriber, "tcp://localhost:5565");

    //  发送同步消息
    void* sync = zmq_socket(context, ZMQ_PUSH);
    zmq_connect(sync, "tcp://localhost:5564");
    s_send(sync, "");

    //  获取更新，并按指令退出
    while (1) {
        char* string = s_recv(subscriber);
        printf("%s\n", string);
        if (strcmp(string, "END") == 0) {
            free(string);
            break;
        }
        free(string);
    }
    zmq_close(sync);
    zmq_close(subscriber);
    zmq_term(context);
    return 0;
}