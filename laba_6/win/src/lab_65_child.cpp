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
    HANDLE event = OpenEvent(EVENT_ALL_ACCESS, FALSE, TEXT("LAB65"));

    WaitForSingleObject(event, INFINITE);
    SetEvent(event);

    for (int i = 1; i <= 90; i++)
    {
        printf("[ %s ] %d. PID:  %d\n", nameProc, i, pid);
        Sleep(100);
    }

    CloseHandle(event);
    system("pause");
    return 0;
}