#include <iostream>
#include <Windows.h>

int main()
{
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();
    const int COUNT_ITER = 1'000;

    for (int i = 0; i < COUNT_ITER; i++)
    {
        std::cout << "PID Selicky = " << pid << ", TID = " << tid << std::endl;
        Sleep(1000);
    }
}