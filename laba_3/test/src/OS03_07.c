#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = getpid(); 
    printf("Parent Process ID: %d\n", pid);

    char* const argv[] = { "ps", "-ef", 0 };
	
	execv("/media/niikola/Nikoals/Univer/OS/laba_3/test/res/OS03_05_1", argv);

    for (int i = 0; i < 100; ++i) {
        printf("Parent Process(%d) Iter: %d\n", pid, i + 1);
        sleep(1);
    }

    return 0;
}