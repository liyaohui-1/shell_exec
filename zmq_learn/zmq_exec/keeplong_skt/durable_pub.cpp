//
//  发布者 - 连接持久化的发布者
//
#include "zhelpers.h"
#include <unistd.h>

int main(void)
{
    void* context = zmq_ctx_new();

    //  订阅者会发送已就绪的消息
    void* sync = zmq_socket(context, ZMQ_PULL);
    zmq_bind(sync, "tcp://*:5564");

    //  使用该套接字发布消息
    void* publisher = zmq_socket(context, ZMQ_PUB);
    zmq_bind(publisher, "tcp://*:5565");

    //  等待同步消息
    char* string = s_recv(sync);
    free(string);

    //  广播10条消息，一秒一条
    int update_nbr;
    for (update_nbr = 0; update_nbr < 1000; update_nbr++) {
        char string[20];
        sprintf(string, "Update %d", update_nbr);
        s_send(publisher, string);
        sleep(1);
    }
    s_send(publisher, "END");

    zmq_close(sync);
    zmq_close(publisher);
    zmq_ctx_destroy(context);
    return 0;
}