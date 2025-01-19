#include <iostream>
#include <windows.h>

using namespace std;

DWORD pid = NULL;
int check;

void enterCriticalSectionAsm() 
{
    __asm
    {
    CriticalSection:
        lock bts check, 0;
        jc CriticalSection;
    }
}

void leaveCriticalSectionAsm() 
{
    __asm lock btr check, 0
}

DWORD WINAPI childThred()
{
    DWORD tid = GetCurrentThreadId();
    enterCriticalSectionAsm();

    for (int i = 0; i < 100; i++)
    {
        cout << "PID: " << pid << " - TID (child): " << tid << " - " << i << endl;
        Sleep(40);
    }

    leaveCriticalSectionAsm();

    return 0;
}

int main()
{
    pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();
    DWORD childId = NULL;
    HANDLE hChild = CreateThread(
        NULL, 
        0, 
        (LPTHREAD_START_ROUTINE)childThred, 
        NULL, 
        0, 
        &childId);
    
    enterCriticalSectionAsm();

    for (int i = 0; i < 100; i++)
    {
        cout << "PID: " << pid << " - TID (main): " << tid << " - " << i << endl;
        Sleep(40);
    }

    leaveCriticalSectionAsm();

    WaitForSingleObject(hChild, INFINITE);
    CloseHandle(hChild);

    system("pause");
    return 0;
}