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
    HANDLE mutex;
    HANDLE processes[SIZE];

    char adressA[]  = "D:\\Univer\\OS\\laba_6\\win\\build\\lab_63A.exe LAB63_A";
    char adressB[]  = "D:\\Univer\\OS\\laba_6\\win\\build\\lab_63B.exe LAB63_B";

    processes[0] = createProcess((LPTSTR)adressA).hProcess;
    processes[1] = createProcess((LPTSTR)adressB).hProcess;

    mutex = CreateMutex(NULL, FALSE, TEXT("LAB63"));
    
    for (int i = 1; i <= 90; i++)
    {
        printf("[ LAB63 ] %d. PID:  %d\n", i, pid);
        
        if (i == 30){
            WaitForSingleObject(mutex, INFINITE);
        }

        if (i == 60){
            ReleaseMutex(mutex);
        }

        Sleep(100);
    }

    WaitForMultipleObjects(SIZE, processes, TRUE, INFINITE);
    for (int i = 0; i < SIZE; i++){
        CloseHandle(processes[i]);
    }

    CloseHandle(mutex);
    system("pause");
    return 0;
}