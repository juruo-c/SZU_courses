#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int ProcessNumber = 1;

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        puts("Please use ./p4 [argument] !");
        exit(-1);   
    }
    else if (argc > 2) 
    {
        puts("Too many Arguments!");
        exit(-1);
    }

    int d = atoi(argv[1]);int pid1, pid2;
    printf("I am process No. %d with PID %d and PPID %d\n", ProcessNumber, getpid(), getppid());
    for (int i = 0; i < d - 1; i ++ )
    {
        switch(pid1 = fork())
        {
            case 0: ProcessNumber *= 2; break;
            case -1: perror("Fork Error!"); exit(1); break;
            default:
                switch(pid2 = fork())
                {
                    case 0:ProcessNumber = ProcessNumber * 2 + 1; break;
                    case -1: perror("Fork Error!"); exit(1); break;
                    default: waitpid(pid1, NULL, 0); waitpid(pid2, NULL, 0); exit(0);
                }
        }
        printf("I am process No. %d with PID %d and PPID %d\n", ProcessNumber, getpid(), getppid());
    }

    return 0;
}