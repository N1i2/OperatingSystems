#include <Windows.h>
#include <iostream>
#include <chrono>
#include <thread>

int i = 0;
auto start = std::chrono::steady_clock::now();
std::chrono::seconds passTime;

void TimerThread(HANDLE hTimer)
{
    long long it = -30000000;
    SetWaitableTimer(hTimer, (LARGE_INTEGER*)&it, 3000, NULL, NULL, FALSE);  

    while (true)
    {
        WaitForSingleObject(hTimer, INFINITE); 

        printf("Iteration:\t%d\n", ++i);

        auto end = std::chrono::steady_clock::now();
        std::chrono::seconds passTime = std::chrono::duration_cast<std::chrono::seconds>(end - start);

        if (passTime.count() >= 15) {
            break;
        }
    }
}

int main()
{
    HANDLE hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
    if (hTimer == NULL) {
        std::cerr << "Failed to create timer." << std::endl;
        return 1;
    }

    std::thread timerThread(TimerThread, hTimer);

    while (true)
    {
        ++i;

        auto end = std::chrono::steady_clock::now();
        std::chrono::seconds passTime = std::chrono::duration_cast<std::chrono::seconds>(end - start);

        if (passTime.count() >= 15) {
            break;
        }
    }

    timerThread.join();

    CloseHandle(hTimer);

    return 0;
}
