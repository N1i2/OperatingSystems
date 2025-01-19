#include <iostream>
#include <windows.h>
#include <bitset>

int main() {
    DWORD processId = GetCurrentProcessId();
    std::cout << "PID: " << processId << std::endl;

    DWORD threadId = GetCurrentThreadId();
    std::cout << "TID: " << threadId << std::endl;

    DWORD processPriorityClass = GetPriorityClass(GetCurrentProcess());
    switch (processPriorityClass)
    {
    case IDLE_PRIORITY_CLASS:std::cout << "IDLE_PRIORITY_CLASS" << std::endl; break;
    case BELOW_NORMAL_PRIORITY_CLASS:std::cout << "BELOW_NORMAL_PRIORITY_CLASS" << std::endl; break;
    case NORMAL_PRIORITY_CLASS:std::cout << "NORMAL_PRIORITY_CLASS" << std::endl; break;
    case ABOVE_NORMAL_PRIORITY_CLASS:std::cout << "ABOVE_NORMAL_PRIORITY_CLASS" << std::endl; break;
    case HIGH_PRIORITY_CLASS:std::cout << "HIGH_PRIORITY_CLASS" << std::endl; break;
    case REALTIME_PRIORITY_CLASS:std::cout << "REALTIME_PRIORITY_CLASS" << std::endl; break;
    default:std::cout << "SOMTHING_NEW" << std::endl; break;
    }

    int threadPriority = GetThreadPriority(GetCurrentThread());
    std::cout << "TP: " << threadPriority << std::endl;

    DWORD_PTR processAffinityMask, systemAffinityMask;
    if (GetProcessAffinityMask(GetCurrentProcess(), &processAffinityMask, &systemAffinityMask)) {
        std::cout << "PAM: " << std::bitset<sizeof(DWORD_PTR) * 8>(processAffinityMask) << std::endl;
    }
    else {
        std::cerr << "Error mask" << std::endl;
    }

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    std::cout << "all umber: " << sysInfo.dwNumberOfProcessors << std::endl;

    DWORD processorNumber = GetCurrentProcessorNumber();
    std::cout << "curent number: " << processorNumber << std::endl;

    return 0;
}