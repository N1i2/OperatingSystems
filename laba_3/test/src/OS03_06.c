#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = getpid(); 
    printf("Parent Process ID: %d\n", pid);

    int result = system("./res/OS03_05_1");

    if (result == -1) {
        perror("System call failed");
        return 1;
    }

    for (int i = 0; i < 100; ++i) {
        printf("PID(%d) Iter: %d\n", pid, i + 1);
        sleep(1);
    }

    return 0;
}
