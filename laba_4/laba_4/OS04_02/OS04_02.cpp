#include <iostream>
#include <windows.h>
#include <thread>

void OS04_02_T1() {
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();
    const int COUNT_ITER = 50;

    for (int i = 0; i < COUNT_ITER; i++) {
        std::cout << i + 1 << ")T1 PID = " << pid << ", TID = " << tid << std::endl;
        Sleep(1000);
    }
}

void OS04_02_T2() {
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();
    const int COUNT_ITER = 125;

    for (int i = 0; i < COUNT_ITER; i++) {
        std::cout << i + 1 << ")T1 PID = " << pid << ", TID = " << tid << std::endl;
        Sleep(1000);
    }
}

int main()
{
    DWORD pid = GetCurrentProcessId();

    std::thread t1(OS04_02_T1);
    std::thread t2(OS04_02_T2);
    const int COUNT_ITER = 100;

    for (int i = 0; i < COUNT_ITER; i++) {
        std::cout <<  i + 1 << ")Sealicky PID = " << pid << std::endl;
        Sleep(1000);
    }

    t1.join();
    t2.join();

    return 0;
}