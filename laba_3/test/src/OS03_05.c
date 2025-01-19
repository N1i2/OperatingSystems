#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void cycle(int counter, char *message)
{
    for (int i = 1; i <= counter; ++i)
    {
        printf("Mess(%s) PID(%d) Iter: %d\n", message, getpid(), i + 1);
        sleep(1);
    }
}

int main()
{
    const int FIRST_COUNT_ITER = 50;
    const int SECOND_COUNT_ITER = 100;

    pid_t pid = getpid();
    printf("Parent Process ID: %d\n", pid);

    switch (pid = fork())
    {
    case -1:
        perror("Fork() returned -1");
        return -1;
    case 0:
        cycle(FIRST_COUNT_ITER, "OS03_05_1");
        return 1;
    default:
        cycle(SECOND_COUNT_ITER, "OS03_05");
        wait(0);
    }

    return 0;
}