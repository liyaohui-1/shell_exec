//
//  气象信息更新服务
//  绑定PUB套接字至tcp://*:5556端点
//  发布随机气象信息
//
#include <zhelpers.h>

int main(void)
{
    //  准备上下文和PUB套接字
    void* context = zmq_ctx_new();
    void* publisher = zmq_socket(context, ZMQ_PUB);
    zmq_bind(publisher, "tcp://*:5556");
    zmq_bind(publisher, "ipc://weather.ipc");

    //  初始化随机数生成器
    srandom((unsigned)time(NULL));
    while (1) {
        //  生成数据
        int zipcode, temperature, relhumidity;
        zipcode = randof(100000);
        temperature = randof(215) - 80;
        relhumidity = randof(50) + 10;

        //  向所有订阅者发送消息
        char update[20];
        sprintf(update, "%05d %d %d", zipcode, temperature, relhumidity);
        s_send(publisher, update);
    }
    zmq_close(publisher);
    zmq_ctx_destroy(context);
    return 0;
}