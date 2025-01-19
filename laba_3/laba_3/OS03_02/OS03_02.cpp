#include <iostream>
#include <windows.h>

int main() {
    const int COUNT_ITER = 100;
    const char* ADRESS_1 = "D:\\Univer\\OS\\laba_3\\laba_3\\x64\\Debug\\OS03_02_1.exe";
    const char* ADRESS_2 = "D:\\Univer\\OS\\laba_3\\laba_3\\x64\\Debug\\OS03_02_2.exe";

    DWORD processId = GetCurrentProcessId();
    std::cout << "Process ID: " << processId << std::endl;

    STARTUPINFO si1, si2;
    PROCESS_INFORMATION pi1, pi2;

    ZeroMemory(&si1, sizeof(si1));
    si1.cb = sizeof(si1);
    ZeroMemory(&pi1, sizeof(pi1));

    ZeroMemory(&si2, sizeof(si2));
    si2.cb = sizeof(si2);
    ZeroMemory(&pi2, sizeof(pi2));

    if (!CreateProcess(ADRESS_1, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si1, &pi1)) {
        std::cerr << "Failed to create process OS03_02_1." << std::endl;
        return 1;
    }

    if (!CreateProcess(ADRESS_2, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2)) {
        std::cerr << "Failed to create process OS03_02_2." << std::endl;
        return 1;
    }

    for (int i = 0; i < 100; ++i) {
        std::cout << "Iter: " << i + 1 << std::endl;
        Sleep(1000);
    }

    WaitForSingleObject(pi1.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);

    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);
    CloseHandle(pi2.hProcess);
    CloseHandle(pi2.hThread);

    std::cout << "OS03_02 end." << std::endl;

    return 0;
}
