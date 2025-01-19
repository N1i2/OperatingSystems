#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h>

int main() {
    std::cout<< getpid() <<std::endl;
    for (int i = 0; i < 1000000; ++i) {
        std::cout << "Step: " << i << std::endl;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
    }

    std::cout << "OS08_03 finished." << std::endl;
    return 0;
}
