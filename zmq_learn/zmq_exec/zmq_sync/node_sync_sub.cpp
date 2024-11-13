//
//  订阅者 - 同步版
//
#include "zhelpers.h"
#include <unistd.h>

int main(void)
{
    void* context = zmq_ctx_new();

    //  一、连接SUB套接字
    void* subscriber = zmq_socket(context, ZMQ_SUB);
    zmq_connect(subscriber, "tcp://localhost:5561");
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "", 0);

    //  ZMQ太快了，我们延迟一会儿……
    sleep(1);

    //  二、与发布者进行同步
    void* syncclient = zmq_socket(context, ZMQ_REQ);
    zmq_connect(syncclient, "tcp://localhost:5562");

    //  - 发送请求
    s_send(syncclient, "");

    //  - 等待应答
    char* string = s_recv(syncclient);
    free(string);

    //  三、处理消息
    int update_nbr = 0;
    while (1) {
        char* string = s_recv(subscriber);
        if (strcmp(string, "END") == 0) {
            free(string);
            break;
        }
        free(string);
        update_nbr++;
    }
    printf("收到 %d 条消息\n", update_nbr);

    zmq_close(subscriber);
    zmq_close(syncclient);
    zmq_ctx_destroy(context);
    return 0;
}