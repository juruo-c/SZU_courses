#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global = 5;

int main(int argc, char* argv[])
{   
    if (fork() == 0)
    {
        printf("Child global = %d\n", global);
        global = 114514;
        exit(0);
    }
    global ++;
    sleep(1);
    printf("Parent global = %d\n", global);
    return 0;
}