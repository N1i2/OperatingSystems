#include <iostream>
#include <windows.h>

int main() {
    DWORD processId = GetCurrentProcessId();
    const int COUNT_ITER = 1000;

    std::cout << "Process ID: " << processId << std::endl;

    for (int i = 0; i < COUNT_ITER; ++i) {
        std::cout << "Iter: " << i + 1 << std::endl;
        Sleep(1000);
    }

    std::cout << "The end." << std::endl;

    return 0;
}
