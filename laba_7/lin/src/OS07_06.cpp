#include <iostream>
#include <csignal>
#include <chrono>
#include <ctime>
#include <unistd.h>

volatile bool stop = false;

void signalHandler(int signal) {
    if (signal == SIGINT) {
        stop = true;
    }
}

int main() {
    std::signal(SIGINT, signalHandler);

    unsigned long long iterationCount = 0;

    auto startRealTime = std::chrono::high_resolution_clock::now();
    clock_t startCpuTime = clock();

    while (!stop) {
        ++iterationCount;
        clock_t currentCpuTime = clock();
        double cpuTimeElapsed = static_cast<double>(currentCpuTime - startCpuTime) / CLOCKS_PER_SEC;

        if (cpuTimeElapsed >= 2.0) {
            std::cout<< "Iteration: "<< iterationCount << std::endl;

            startCpuTime = currentCpuTime;

            break;
        }
    }

    auto endRealTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> realTimeElapsed = endRealTime - startRealTime;

    std::cout << "Real time: " << realTimeElapsed.count() << " s\n";
    return 0;
}