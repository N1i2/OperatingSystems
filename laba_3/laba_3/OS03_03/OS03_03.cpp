#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <tchar.h>

#pragma comment(lib, "psapi.lib")

void PrintProcessNameAndID(DWORD processID) {
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

    if (hProcess != NULL) {
        HMODULE hMod;
        DWORD cbNeeded;

        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
            GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
        }
    }

    std::wcout << L"Process ID: " << processID << L"\tProcess Name: " << szProcessName << std::endl;

    CloseHandle(hProcess);
}

int main() {
    DWORD aProcesses[1024], cbNeeded, cProcesses;

    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
        std::cerr << "EnumProcesses failed." << std::endl;
        return 1;
    }

    cProcesses = cbNeeded / sizeof(DWORD);

    std::wcout << L"List of processes running in the system:\n" << std::endl;

    for (unsigned int i = 0; i < cProcesses; i++) {
        if (aProcesses[i] != 0) {
            PrintProcessNameAndID(aProcesses[i]);
        }
    }

    return 0;
}