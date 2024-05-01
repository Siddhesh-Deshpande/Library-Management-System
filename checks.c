#include"header.h"
void record_transaction(char *username,int isbn,int fd)
{
    // int fd = open("transaction.txt",O_RDWR|O_CREAT,0666);
    lseek(fd,0,SEEK_END);
    Transaction t;
    strcpy(t.person_name,username);
    t.isbn = isbn;
    t.return_status = 0;
    write(fd,&t,sizeof(Transaction));
    // close(fd);
}
bool check_return_status(char *username,int isbn) // Required for returning the book we need to chek if the book has been returned or not.
{
    int fd = open("transaction.txt",O_RDWR|O_CREAT,0666);
    Transaction t;
    while(read(fd,&t,sizeof(Transaction)))
    {
        if(strcmp(t.person_name,username)==0 && t.isbn==isbn)
        {
            if(t.return_status==0) // book not returned so allow return;
            {
                t.return_status=1;
                lseek(fd,-sizeof(Transaction),SEEK_CUR);
                write(fd,&t,sizeof(Transaction));
                close(fd);
                return true;
            }
        }
    }
    close(fd);
    return false;
}
bool can_issue(char *username,int isbn)
{
    int fd = open("transaction.txt",O_RDWR|O_CREAT,0666);
    Transaction t;
    while(read(fd,&t,sizeof(Transaction)))
    {
        if(strcmp(t.person_name,username)==0 && t.isbn==isbn)
        {
            if(t.return_status==0) //boook has not been returned so cannot issue again.
            {
                close(fd);
                return false;
            }
        }
    }
    record_transaction(username,isbn,fd);
    close(fd);
    return true;
}

