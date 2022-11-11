#ifndef _CLIENTINFO_
#define _CLIENTINFO_

typedef struct 
{
    char username[100];
    char password[100];
    char fifo[100];
}REGISTERINFO, *REGISTERINFOPTR;

typedef struct 
{
    char username[100];
    char password[100];
}LOGININFO, *LOGININFOPTR;

typedef struct 
{
    char username[100];
    char message[100005];
}MESSAGEINFO, *MESSAGEINFOPTR;

#endif