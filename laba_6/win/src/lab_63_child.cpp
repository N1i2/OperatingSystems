#include <iostream>
#include <Windows.h>

int main(int argc, char* argv[])
{
    const char* nameProc = "Child Process";

    if (argc == 2)
    {
        nameProc = argv[1];
    }

    int pid = GetCurrentProcessId();
    HANDLE mutex = OpenMutex(SYNCHRONIZE, FALSE, TEXT("LAB63"));

    for (int i = 1; i <= 90; i++)
    {
        printf("[ %s ] %d. PID:  %d\n", nameProc, i, pid);
        
        if (i == 30){
            WaitForSingleObject(mutex, INFINITE);
        }

        if (i == 60){
            ReleaseMutex(mutex);
        }

        Sleep(100);
    }

    CloseHandle(mutex);

    system("pause");
    return 0;
}