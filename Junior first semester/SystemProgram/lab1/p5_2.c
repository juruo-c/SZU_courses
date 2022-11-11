#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int pid1, ppid1, pgrp1;
    scanf("%d%d%d", &pid1, &ppid1, &pgrp1);
    printf("%d %d %d %d %d %d", pid1, ppid1, pgrp1, getpid(), getppid(), getpgrp());
    return 0;
}