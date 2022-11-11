#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if (fork() == 0)
    {
        printf("Child ID: %d\n", getpid());
        exit(0);
    }
    printf("Parent ID: %d\n", getpid());
    while (1);
    return 0;
}