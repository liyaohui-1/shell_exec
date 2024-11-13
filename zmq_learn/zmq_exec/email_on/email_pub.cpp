//
//  发布-订阅消息信封 - 发布者
//  s_sendmore()函数也是zhelpers.h提供的
//
#include "zhelpers.h"
#include <unistd.h>

int main(void)
{
    //  准备上下文和PUB套接字
    void* context = zmq_init(1);
    void* publisher = zmq_socket(context, ZMQ_PUB);
    zmq_bind(publisher, "tcp://*:5563");

    while (1) {
        //  发布两条消息，A类型和B类型
        s_sendmore(publisher, "A");
        s_send(publisher, "We don't want to see this");
        s_sendmore(publisher, "B");
        s_send(publisher, "We would like to see this");
        sleep(1);
    }
    //  正确退出
    zmq_close(publisher);
    zmq_term(context);
    return 0;
}