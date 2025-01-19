#include <iostream>
#include <windows.h>
#include <iomanip>

#define SIZE 2

using namespace std;

CRITICAL_SECTION cs;

void WINAPI loopFunction(char* displayedName) 
{
    int pid = GetCurrentProcessId(); 
    int tid = GetCurrentThreadId();  
    for (int i = 0; i <= 90; ++i)
    {
        if (i == 30){
            EnterCriticalSection(&cs);
        }
        if (i == 60){
            LeaveCriticalSection(&cs);
        }
        printf("%d.\t(%s) \tPID: [ %d ] TID: [ %u ]\n", i, displayedName, pid, tid); 
        Sleep(100); 
    }
}

int main()
{
    int pid = GetCurrentProcessId();
    DWORD childId_1 = NULL; 
    DWORD childId_2 = NULL; 

    HANDLE thread[SIZE]; 

    thread[0] = CreateThread(
        NULL, 
        0, 
        (LPTHREAD_START_ROUTINE)loopFunction, 
        (char*)"Thread A", 
        0, 
        &childId_1);

    thread[1] = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)loopFunction,
        (char*)"Thread B",
        0,
        &childId_2);

    InitializeCriticalSection(&cs); 

    loopFunction((char*)"Main");

    WaitForMultipleObjects(SIZE, thread, TRUE, INFINITE); 

    CloseHandle(thread[0]); 
    CloseHandle(thread[1]); 

    DeleteCriticalSection(&cs); 

    system("pause"); 
    return 0;
}