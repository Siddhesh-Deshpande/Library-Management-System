#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/socket.h>
#include<string.h>
#include<stdbool.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "transaction.h"
//to identify the operation to perform.
#define ISSUE_BOOK 3
#define RETURN_BOOK 4
#define ADD_USER 1
#define ADD_BOOK 2
#define GET_BOOK 5
#define MODIFY_BOOK 6

void add_log(char *information);
bool check_user(char *username,char *password);
int  login_user();