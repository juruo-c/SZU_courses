/*
    define the data structure of each client's infomation
    1. client's fifo name
    2. left argument and right argument
    3. oprator
*/
#ifndef _CLIENTINFO_H
#define _CLIENTINFO_H

typedef struct 
{
    char myfifo[100];
    int leftarg;
    int rightarg;
    char op;
}CLIENTINFO, *CLIENTINFOPTR;

#endif 
