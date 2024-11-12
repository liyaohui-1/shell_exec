//
//  Hello World 服务端
//  绑定一个REP套接字至tcp://*:5555
//  从客户端接收Hello，并应答World
//
#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

int main(void)
{
    void* context = zmq_init(1);

    //  与客户端通信的套接字
    void* responder = zmq_socket(context, ZMQ_REP);
    zmq_bind(responder, "tcp://*:5555");

    while (1) {
        //  等待客户端请求
        zmq_msg_t request;
        zmq_msg_init(&request);
        zmq_msg_recv(&request, responder, 0);

        size_t size = zmq_msg_size(&request);
        char* data = (char*)zmq_msg_data(&request);
        data[size] = '\0'; // 确保字符串以null结尾（如果数据不是字符串或包含null字符，则此操作可能不安全）

        printf("接收到数据：%s,长度是：%zu\n", data, size);

        //  做些“处理”
        sleep(1);

        //  返回应答
        zmq_msg_t reply;
        zmq_msg_init_size(&reply, 6); // "World" + null terminator
        memcpy(zmq_msg_data(&reply), "World", 5);
        ((char*)zmq_msg_data(&reply))[5] = '\0'; // 确保字符串以null结尾

        zmq_msg_send(&reply, responder, 0);
        zmq_msg_close(&request);
        zmq_msg_close(&reply);
    }

    //  注意：在实际应用中，您应该有一种机制来优雅地退出这个循环，
    //  比如监听一个信号或使用一个条件变量。

    //  清理资源（但在这个例子中，由于循环是无限的，这些代码永远不会被执行）
    zmq_close(responder);
    zmq_term(context);

    return 0; // 注意：这个返回值在这个例子中永远不会被看到，因为程序不会退出循环。
}