//
//  气象信息客户端
//  连接SUB套接字至tcp://*:5556端点
//  收集指定邮编的气象信息，并计算平均温度
//
#include <zhelpers.h>

int main(int argc, char* argv[])
{
    void* context = zmq_ctx_new();

    //  创建连接至服务端的套接字
    printf("正在收集气象信息...\n");
    void* subscriber = zmq_socket(context, ZMQ_SUB);
    zmq_connect(subscriber, "tcp://localhost:5556");

    //  设置订阅信息，默认为纽约，邮编10001
    const char* filter = (argc > 1) ? argv[1] : "10001 ";
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, filter, strlen(filter));

    //  处理100条更新信息
    int update_nbr;
    long total_temp = 0;
    for (update_nbr = 0; update_nbr < 10; update_nbr++) {
        char* string = s_recv(subscriber);
        int zipcode, temperature, relhumidity;
        sscanf(string, "%d %d %d", &zipcode, &temperature, &relhumidity);
        total_temp += temperature;
        free(string);
    }
    printf("地区邮编 '%s' 的平均温度为 %dF\n", filter, (int)(total_temp / update_nbr));

    zmq_ctx_destroy(subscriber);
    zmq_term(context);
    return 0;
}