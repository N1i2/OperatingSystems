#include<stdio.h>
#include <unistd.h>

int main(){
    const int COUNT_ITER = 100;

    int pid = getpid();
    printf("Process ID: %d\n", pid);

    for (int i = 0; i < COUNT_ITER; i++)
    {
        printf("Iter: %d\n", i + 1);
        sleep(1);
    }
    

    printf("\n");
    return 0;
}