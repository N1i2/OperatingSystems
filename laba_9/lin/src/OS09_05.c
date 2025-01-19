#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <locale.h>

int main()
{
	char *locale = setlocale(LC_ALL, "");
    char ch;
    int rowNumber = 1;
    int in = open("/media/niikola/Nikoals/Univer/OS/laba_9/OS09_05.txt", O_RDONLY);

    while (read(in,&ch,1) == 1)
    {
        if(ch == '\n')
        {
            rowNumber++;
        }
    }

    printf("Rows quantity: %d \n",rowNumber);
    return 0;
}