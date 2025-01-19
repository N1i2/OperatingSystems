#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <locale.h>

int main(int argc, char *argv[])
{
    int number;  
    char* locale = setlocale(LC_ALL, "ru_RU.UTF-8");
    char ch[1];
    int in = open("/media/niikola/Nikoals/Univer/OS/laba_9/OS09_05.txt",O_RDONLY);
    int out;
    _Bool evenNumber = 0;
    if(argc != 2)
    {
        printf("One number argument is required: odd number - odd rows, even number - even rows\n");
        exit(1);
    }
    number = atoi(argv[1]);
    printf("Params: %d\n",number);
    if(number % 2 != 0)
    {
        out = open("/media/niikola/Nikoals/Univer/OS/laba_9/OS09_05_01.txt",O_RDWR|O_CREAT);
    }
    else 
    {
        out = open("/media/niikola/Nikoals/Univer/OS/laba_9/OS09_05_02.txt",O_RDWR|O_CREAT);
    }

    evenNumber = (number % 2);

    while (read(in,&ch,1) != 1)
    {
        if(evenNumber == 0)
        {
            write(out,&ch,1);
        }
        if(*ch == '\n')
        {	
            evenNumber = !evenNumber;
        }
    }
    exit(0);
}