#include <iostream>
#include <ctime>

int main(int argc, char* argv[]) {
    int iteration = 0;
    clock_t start = clock();

    bool printed5 = false, printed10 = false; 

    while (true) {
        clock_t end = clock();
        double timer = (((double)(end - start)) / CLOCKS_PER_SEC);
        ++iteration;

        if (!printed5 && timer >= 5 && timer < 10) {
            std::cout << "Iterations at 5 seconds: " << iteration << std::endl;
            printed5 = true;
        }
        if (!printed10 && timer >= 10 && timer < 15) {
            std::cout << "Iterations at 10 seconds: " << iteration << std::endl;
            printed10 = true;
        }
        if (timer >= 15) {
            break;
        }
    }

    std::cout << "\nResult: " << iteration << std::endl;

    return 0;
}
