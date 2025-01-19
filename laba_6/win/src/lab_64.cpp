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
    HANDLE semaphore;
    HANDLE processes[SIZE];

    char adressA[] = "D:\\Univer\\OS\\laba_6\\win\\build\\lab_64A.exe LAB64_A";
    char adressB[] = "D:\\Univer\\OS\\laba_6\\win\\build\\lab_64B.exe LAB64_B";

    processes[0] = createProcess((LPTSTR)adressA).hProcess;
    processes[1] = createProcess((LPTSTR)adressB).hProcess;

    semaphore = CreateSemaphore(NULL, 2, 2, TEXT("LAB64"));

    for (int i = 1; i <= 90; i++)
    {
        printf("[ LAB64 ] %d. PID:  %d\n", i, pid);
        
        if (i == 30){
            WaitForSingleObject(semaphore, INFINITE);
        }

        if (i == 60){
            ReleaseSemaphore(semaphore, 1, NULL);
        }

        Sleep(100);
    }

    WaitForMultipleObjects(SIZE, processes, TRUE, INFINITE);
    for (int i = 0; i < SIZE; i++){
        CloseHandle(processes[i]);
    }

    CloseHandle(semaphore);
    return 0;
}