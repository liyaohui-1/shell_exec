//
//  Hello World 客户端
//  连接REQ套接字至 tcp://localhost:5555
//  发送Hello给服务端，并接收World
//
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <zmq.hpp>

int main(void)
{
    zmq::context_t context(1);

    //  连接至服务端的套接字
    std::cout << "正在连接至hello world服务端..." << std::endl;
    zmq::socket_t requester(context, ZMQ_REQ);
    requester.connect("tcp://localhost:5555");

    for (int request_nbr = 0; request_nbr < 10; request_nbr++) {
        zmq_msg_t request;
        zmq_msg_init_size(&request, 5);
        memcpy(zmq_msg_data(&request), "Hello", 5);
        std::cout << "正在发送 Hello , " << request_nbr + 1 << "..." << std::endl;
        zmq_msg_send(&request, requester, 0);
        zmq_msg_close(&request);

        zmq_msg_t reply;
        zmq_msg_init(&reply);
        zmq_msg_recv(&reply, requester, 0);
        std::string reply_str(static_cast<char*>(zmq_msg_data(&reply)), zmq_msg_size(&reply));
        std::cout << "接收到数据：" << reply_str << "，长度是：" << zmq_msg_size(&reply) << std::endl;
        zmq_msg_close(&reply);
    }
    requester.close();
    context.close();
    return 0;
}