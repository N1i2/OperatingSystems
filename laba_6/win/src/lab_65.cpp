#include <iostream>
#include <Windows.h>

#define SIZE 2

using namespace std;

PROCESS_INFORMATION createProcess(LPTSTR cmd)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    if (CreateProcess(
            NULL,
            cmd,
            NULL,
            NULL,
            FALSE,
            CREATE_NEW_CONSOLE,
            NULL,
            NULL,
            &si,
            &pi))
    {
        cout << "Process created\n";
    }
    else
    {
        cout << "Error CreateProcess\n";
    }

    return pi;
}

int main()
{
    int pid = GetCurrentProcessId();
    HANDLE event;
    HANDLE processes[SIZE];

    char adressA[] = "D:\\Univer\\OS\\laba_6\\win\\build\\lab_65A.exe LAB65_A";
    char adressB[] = "D:\\Univer\\OS\\laba_6\\win\\build\\lab_65B.exe LAB65_B";

    processes[0] = createProcess((LPTSTR) adressA).hProcess;
    processes[1] = createProcess((LPTSTR) adressB).hProcess;

    event = CreateEvent(NULL, FALSE, FALSE, TEXT("LAB65")); 

    for (int i = 1; i <= 90; i++)
    {
        printf("[ LAB65 ] %d. PID:  %d\n", i, pid);

        if (i == 15){
            SetEvent(event);
        }

        Sleep(100);
    }

    WaitForMultipleObjects(SIZE, processes, TRUE, INFINITE);
    for (int i = 0; i < SIZE; i++){
        CloseHandle(processes[i]);
    }

    CloseHandle(event);
    system("pause");
    return 0;
}