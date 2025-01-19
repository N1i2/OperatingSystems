#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

using namespace std;

// Глобальный мьютекс для синхронизации
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char* argv[]) {
    const char* nameProc = "Child Process";

    if (argc == 2) {
        nameProc = argv[1];
    }

    pid_t pid = getpid();

    // Дочерний процесс начинает работу
    for (int i = 1; i <= 90; i++) {
        printf("[ %s ] %d. PID: %d\n", nameProc, i, pid);

        if (i == 30) {
            pthread_mutex_lock(&mutex);  // Захватить мьютекс
        }

        if (i == 60) {
            pthread_mutex_unlock(&mutex);  // Освободить мьютекс
        }

        usleep(100000);  // Пауза 100 мс
    }

    return 0;
}
