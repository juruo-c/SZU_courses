#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    printf("%d %d %d", getpid(), getppid(), getpgrp());
    return 0;
}