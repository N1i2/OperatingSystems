#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <locale.h>
#include <stdbool.h>


int main(int argc, char *argv[])
{
    char *locale = setlocale(LC_ALL, "");
    int in;
    long pos, offs;               
    char buffer[20];

    in = open("/media/niikola/Nikoals/Univer/OS/laba_9/OS09_05.txt",O_RDONLY);
    
    offs = 10L;
    pos = lseek(in, offs, SEEK_SET);
    printf("SEEK_SET, offset= 10L: %ld\n", pos);
    read(in, buffer, 20);
    printf("READ 20 char from file: %s\n\n", buffer);
    

	offs = 10L;
    pos = lseek(in, offs, SEEK_CUR);
    printf("SEEK_CUR, offset= 10L: = %ld\n", pos);
    read(in, buffer, 20);
    printf("READ 20 char from file: %s\n\n", buffer);

	offs = -20L;
    pos = lseek(in, offs, SEEK_END);
    printf("SEEK_END, offset= -20L: = %ld\n", pos);
    read(in, buffer, 20);
    printf("READ 20 char from file: %s\n\n", buffer);

    offs = 0L;
    pos = lseek(in, offs, SEEK_END);
    printf("SEEK_END, offset= 0L: = %ld\n", pos);

    close(in);
    return 0;
}