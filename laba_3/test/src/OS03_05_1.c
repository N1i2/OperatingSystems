#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int pid = getpid();
    printf("Children Process ID: %d\n", pid);

    for (int i = 0; i < 100; ++i) {
        printf("PID(%d) Iter: %d\n", getpid(), i + 1);
        sleep(1);
    }

    return 0;
}