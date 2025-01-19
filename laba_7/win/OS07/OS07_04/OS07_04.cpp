#include <iostream>
#include <cstdlib>
#include <thread>
#include <windows.h>
#include <string>

std::wstring stringToWstring(const std::string& str) {
    return std::wstring(str.begin(), str.end());
}

void runChildProcess(const std::string& processName, int duration) {
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    std::string command = "cmd.exe /c start " + processName + " " + std::to_string(duration);
    std::wstring wCommand = stringToWstring(command); 

    if (!CreateProcessW(
        nullptr,                       
        const_cast<wchar_t*>(wCommand.c_str()), 
        nullptr,               
        nullptr,               
        FALSE,                 
        0,                     
        nullptr,               
        nullptr,               
        &si,                   
        &pi                    
    )) {
        std::cerr << "Failed to start process: " << processName << "\n";
        return;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

int main() {
    std::thread child1(runChildProcess, "D:\\Univer\\OS\\laba_7\\win\\OS07\\x64\\Debug\\OS07_04_X.exe", 60);
    std::thread child2(runChildProcess, "D:\\Univer\\OS\\laba_7\\win\\OS07\\x64\\Debug\\OS07_04_X.exe", 120);

    child1.join();
    child2.join();

    return 0;
}
