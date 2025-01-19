#include <iostream>
#include <windows.h>

int main() {
    const int COUNT_ITER = 125;

    DWORD processId = GetCurrentProcessId();
    std::cout << "OS03_02_2 Process ID: " << processId << std::endl;

    for (int i = 0; i < COUNT_ITER; ++i) {
        std::cout << "OS03_02_2 Iter: " << i + 1 << std::endl;
        Sleep(1000);
    }

    std::cout << "OS03_02_2 End." << std::endl;
    return 0;
}
