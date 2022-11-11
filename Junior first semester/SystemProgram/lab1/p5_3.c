#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int pid1, ppid1, pgrp1, pid2, ppid2, pgrp2;
    scanf("%d%d%d%d%d%d", &pid1, &ppid1, &pgrp1, &pid2, &ppid2, &pgrp2);
    printf("p5_1: PID = %d PPID = %d PGID = %d\n", pid1, ppid1, pgrp1);
    printf("p5_2: PID = %d PPID = %d PGID = %d\n", pid2, ppid2, pgrp2);
    printf("p5_3: PID = %d PPID = %d PGID = %d\n", getpid(), getppid(), getpgrp());
    return 0;
}