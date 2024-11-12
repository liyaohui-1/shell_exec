//
//  发布者 - 同步版
//
#include "zhelpers.h"

//  等待10个订阅者连接
#define SUBSCRIBERS_EXPECTED 10

int main(void)
{
    void* context = zmq_init(1);

    //  用于和客户端通信的套接字
    void* publisher = zmq_socket(context, ZMQ_PUB);
    zmq_bind(publisher, "tcp://*:5561");

    //  用于接收信号的套接字
    void* syncservice = zmq_socket(context, ZMQ_REP);
    zmq_bind(syncservice, "tcp://*:5562");

    //  接收订阅者的就绪信号
    printf("正在等待订阅者就绪\n");
    int subscribers = 0;
    while (subscribers < SUBSCRIBERS_EXPECTED) {
        //  - 等待就绪信息
        char* string = s_recv(syncservice);
        free(string);
        //  - 发送应答
        s_send(syncservice, "");
        subscribers++;
    }
    //  开始发送100万条数据
    printf("正在广播消息\n");
    int update_nbr;
    for (update_nbr = 0; update_nbr < 1000000; update_nbr++)
        s_send(publisher, "Rhubarb");

    s_send(publisher, "END");

    zmq_close(publisher);
    zmq_close(syncservice);
    zmq_term(context);
    return 0;
}