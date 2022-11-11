#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include "clientinfo.h"

#define FIFO_NAME "/home/szu/zhengyang2020151002/chatapplication/data/server_fifo/chat_server_fifo"
#define BUFF_SZ 100

char mypipename[BUFF_SZ];

/* remove pipe if signaled */
void handler(int sig) 
{
    unlink(mypipename);
    exit(1);
}

int main(int argc, char* argv[]) 
{
    int res;
    int fifo_fd, my_fifo;
    int fd;
    CLIENTINFO info;
    char buffer[BUFF_SZ];

    printf("res's address = 0x%x fifo_fd's address = 0x%x my_fifo's address = 0x%x\n"
    , &res, &fifo_fd, &my_fifo);
    printf("fd's address = 0x%x info's address = 0x%x buffer's address = 0x%x\n"
    , &fd, &info, buffer);

    /* handle some signals */
    signal(SIGKILL, handler);
    signal(SIGINT, handler);
    signal(SIGTERM, handler);

    /* check for proper command line */
    if (argc != 4)
    {
        printf("Usage: %s op1 operator op2\n", argv[0]);
        exit(1);
    }
    if (strcmp(argv[2], "+") && strcmp(argv[2], "-") && strcmp(argv[2], "*") && strcmp(argv[2], "/"))
    {
        printf("Operator Should be '+', '-', '*' or '/'\n");
        exit(1);
    }

    /* check if server fifo exists */
    if (access(FIFO_NAME, F_OK) == -1) 
    {
        printf("Could not open FIFO %s\n", FIFO_NAME);
        exit(EXIT_FAILURE);
    }
    /* open server fifo for write */
    fifo_fd = open(FIFO_NAME, O_WRONLY);
    if (fifo_fd == -1)
    {
        printf("Could not open %s for write only access\n", FIFO_NAME);
        exit(EXIT_FAILURE);
    }

    /* create my own FIFO */
    sprintf(mypipename, "/home/szu/zhengyang2020151002/chatapplication/data/client_fifo/chat_client%d_fifo", getpid());
    res = mkfifo(mypipename, 0666);
    if (res != 0)
    {
        printf("FIFO %s was not created\n", mypipename);
        exit(EXIT_FAILURE);
    }

    /* construct client info */
    strncpy(info.myfifo, mypipename, strlen(mypipename) + 1);
    info.leftarg = atoi(argv[1]);
    info.op = argv[2][0];
    info.rightarg = atoi(argv[3]);

    printf("mypipename = %s\n", mypipename);
    printf("info.myfifo's len = %d info.myfifo = %s CLIENTINFO's size = %d mypipename's len = %d ", 
    strlen(info.myfifo), info.myfifo, sizeof(CLIENTINFO), strlen(mypipename));
    printf("fifo_fd = %d\n", fifo_fd);

    /* write client info to server fifo */
    if (write(fifo_fd, &info, sizeof(CLIENTINFO)) == -1)
    {
        perror("Failed to write FIFO");
        exit(EXIT_FAILURE);
    }
    close(fifo_fd);

    /* open my own FIFO for reading */
    my_fifo = open(mypipename, O_RDONLY);
    if (my_fifo == -1)
    {
        printf("Could not open %s for read only access\n", mypipename);
        exit(EXIT_FAILURE);
    }

    /* get result from server */
    memset(buffer, '\0', BUFF_SZ);
    res = read(my_fifo, buffer, BUFF_SZ);
    if (res == -1)
    {
        printf("Failed to read FIFO %s\n", mypipename);
        exit(EXIT_FAILURE);
    }
    printf("Received from server: %s\n", buffer);

    printf("Client %d is terminating\n", getpid());

    /* delete fifo from system */
    close(my_fifo);
    unlink(mypipename);

    return 0;
}