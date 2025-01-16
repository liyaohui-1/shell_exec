#include <iostream>
#include <thread>

int main() 
{
    while(true)
    {
        std::cout << "Hello, world!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    return 0;
}