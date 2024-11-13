#include <zmq.h>
#include <zmq.hpp>
#include <iostream>

int main()
{
    int major = 0, minor = 0, patch = 0;
    zmq_version(&major, &minor, &patch);
    std::cout << "zmq_version: " << major << "." << minor << "." << patch << std::endl;
    return 0;
}