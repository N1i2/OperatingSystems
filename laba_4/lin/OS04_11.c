#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* OS04_11_T1(void* arg) {
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    
    for (int i = 0; i < 75; i++) {
        printf("Thread: Process ID: %d, Thread ID: %lu, Iteration: %d\n", pid, tid, i + 1);
        sleep(1);
    }

    return NULL;
}

int main() {
    pthread_t thread;
    pid_t pid = getpid();

    if (pthread_create(&thread, NULL, OS04_11_T1, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    for (int i = 0; i < 100; i++) {
        printf("Main Sealicky: Process ID: %d, Iteration: %d\n", pid, i + 1);
        sleep(1);
    }

    pthread_join(thread, NULL);

    return 0;
}
