#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Start process... (%d)\n", getpid());

    for (long long i = 0; i < 1e10; ++i) {
        if (i % (long long)1e9 == 0) {
            printf("Numb: %lld\n", i);
            sleep(10);
        }
    }

    printf("End.\n");
    return 0;
}
