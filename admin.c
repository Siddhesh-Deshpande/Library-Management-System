#include"person.h"
#include"book.h"
#include"header.h"
void add_log(char *information)
{
    FILE * ptr = fopen("log.txt","a");
    fseek(ptr,0,SEEK_END);
    fprintf(ptr,"%s",information);
    fclose(ptr);
}
bool add_user(Person p)
{
    int fd = open("user_details.txt",O_RDWR|O_CREAT,0666);
    if(fd==-1)
    {
        // printf("User add failed\n");
        add_log("User add failed\n");
        return false;
    }
    int st1 = lseek(fd,0,SEEK_END);
    int st2 = write(fd,&p,sizeof(p));
    if(st1==-1 || st2==-1)
    {
        // printf("User ADD Failed\n");
        add_log("User add failed\n");
        return false;
    }
    add_log("New User ");
    add_log(p.name);
    add_log("has been added \n");
    close(fd);
    return true;
}
bool add_book(Book b)
{
    int fd = open("book_details.txt",O_RDWR|O_CREAT,0666);
    if(fd==-1)
    {
        // printf("Book Add Failed\n");
        add_log("Book Add Failed\n");
        return false;
    }
    int s1 = lseek(fd,0,SEEK_END);
    int s2= write(fd,&b,sizeof(b));
    if(s1==-1 || s2==-1)
    {
        // printf("Book Add Failed\n");
        add_log("Book Add Failed\n");
        return false;
    }
    add_log("New Book ");
    add_log(b.book_name);
    add_log("has been added\n");
    close(fd);
    return true;
}
void get_book(Book *b,int isbn)
{
    int fd = open("book_details.txt",O_RDWR);
    if(fd==-1)
    {
        // printf("Book not found\n");
        add_log("Book ");
        add_log(b->book_name);
        add_log("not found\n");
        return ;
    }
    int s1 = lseek(fd,0,SEEK_SET);
    if(s1==-1)
    {
        // printf("Book not found\n");
        add_log("Book ");
        add_log(b->book_name);
        add_log("not found\n");
        return;
    }
    Book temp;
    while(read(fd,&temp,sizeof(temp)))
    {
        if(temp.isbn==isbn)
        {
            *b=temp;
            close(fd);
            add_log("Details of ");
            add_log(temp.book_name);
            add_log("were obtained successfully\n");
            return;
        }
    }
    // printf("Book Not found\n");
    add_log("Book ");
    add_log(b->book_name);
    add_log("not found\n");
    close(fd);
}
bool modify_book(int isbn, int newval)
{
    int fd = open("book_details.txt",O_RDWR);
    char book_no[10];
    sprintf(book_no,"%d",isbn);
    if(fd==-1)
    {
        add_log("Book with isbn\n");
        add_log(book_no);
        add_log("could not be modified\n");
        return false;
    }
    lseek(fd,0,SEEK_SET);
    Book temp;
    while(read(fd,&temp,sizeof(temp)))
    {
        if(temp.isbn==isbn)
        {
            temp.quantity=newval;
            lseek(fd,-sizeof(temp),SEEK_CUR);
            write(fd,&temp,sizeof(temp));
            close(fd);
            add_log("The quantity of Book ");
            add_log(temp.book_name);
            add_log("has been modified\n");
            return true;
        }
    }
    add_log("Book with isbn\n");
    add_log(book_no);
    add_log("could not be modified\n");
    close(fd);
    return false;
}
