#include <iostream>
#include <unistd.h>
#include <sys/resource.h>

void getPID() {
    pid_t pid = getpid();
    std::cout << "PID: " << pid << std::endl;
}

void getTID() {
    pthread_t tid = pthread_self();
    std::cout << "TID: " << tid << std::endl;
}

void getNicePriority() {
    int priority = getpriority(PRIO_PROCESS, 0);
    std::cout << "TNP: " << priority << std::endl;
}

void getAvailableProcess(){
    cpu_set_t cpuSet;
    CPU_ZERO(&cpuSet);
    sched_getaffinity(0, sizeof(cpu_set_t), &cpuSet);
    std::cout << "CPU: ";
    for (int i = 0; i < CPU_SETSIZE; ++i) {
        if (CPU_ISSET(i, &cpuSet)) {
            std::cout << i << std::endl;
        }
    }
    std::cout << std::endl;
}

int main() {
    getPID();
    getTID();
    getNicePriority();
    getAvailableProcess();

    return 0;
}