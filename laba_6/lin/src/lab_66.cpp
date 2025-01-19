#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* LoopFunction(void* name)
{
    int pid = getpid();

    for (int i = 1; i <= 90; i++)
    {
        if (i == 30 || i == 60)
            pthread_mutex_lock(&mutex);  

        printf("[ %s ] %d. PID = %d\n", (char*)name, i, pid);

        if (i == 30)
            pthread_mutex_unlock(&mutex);  
        else if (i == 60)
            pthread_mutex_unlock(&mutex);  

        usleep(100 * 1000);  
    }

    return NULL;  
}

int main(int argc, char* argv[])
{
    int pid = getpid();
    pthread_t thread1;
    pthread_t thread2;

    pthread_mutex_init(&mutex, NULL);  

    pthread_create(&thread1, NULL, LoopFunction, (void*)"thread A");
    pthread_create(&thread2, NULL, LoopFunction, (void*)"thread B");

    for (int i = 1; i <= 90; i++)
    {
        if (i == 30 || i == 60)
            pthread_mutex_lock(&mutex);  

        printf("[ Main ] %d. PID = %d\n", i, pid);

        if (i == 30)
            pthread_mutex_unlock(&mutex);  
        else if (i == 60)
            pthread_mutex_unlock(&mutex);  

        usleep(100 * 1000);  
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
