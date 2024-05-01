#ifndef TRANSACTION_H
#define TRANSACTION_H
typedef struct Transaction {
    char person_name[100];
    int isbn;
    int return_status;
} Transaction;
bool check_return_status(char *username,int isbn);
bool can_issue(char *username,int isbn);
#endif