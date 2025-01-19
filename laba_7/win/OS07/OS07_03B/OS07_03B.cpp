#include <Windows.h>
#include <iostream>
#include <ctime>
#include<chrono>

int main()
{
    HANDLE hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
    long long it = -30000000;
    SetWaitableTimer(hTimer, (LARGE_INTEGER*)&it, 3000, NULL, NULL, FALSE);
    auto start = std::chrono::steady_clock::now();
    int i = 0;

    while (true)
    {
        WaitForSingleObject(hTimer, INFINITE);

        auto end = std::chrono::steady_clock::now();        
        std::chrono::seconds passTime = std::chrono::duration_cast<std::chrono::seconds>(end - start);

        printf("Iteration after %ld sec:\t%d\n", passTime.count(), ++i);

        if (passTime.count() >= 15) {
            break;
        }
    }

    return 0;
}