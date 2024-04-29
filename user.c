#include"header.h"
#include"book.h"
bool issue_book(int isbn,char *person_name)
{
    int fd = open("book_details.txt",O_RDWR|O_EXCL,0666);
    if(fd==-1)
    {
        // printf("Book Issue Failed1\n");
        add_log("Book Issue Failed1\n");;
        return false;
    }
    lseek(fd,0,SEEK_SET);
    Book temp;
    while(read(fd,&temp,sizeof(temp)))
    {
        if(temp.isbn == isbn && temp.quantity>0)
        {
            struct flock wrlk;
            wrlk.l_type=F_WRLCK;
            wrlk.l_whence=lseek(fd,0,SEEK_CUR)-sizeof(temp);
            wrlk.l_start=0;
            wrlk.l_len=sizeof(temp);
            wrlk.l_pid=getpid();
            fcntl(fd,F_SETLKW,&wrlk);
            temp.quantity--;
            lseek(fd,-sizeof(temp),SEEK_CUR);
            write(fd,&temp,sizeof(temp));
            wrlk.l_type=F_UNLCK;
            fcntl(fd,F_SETLK,&wrlk);
            close(fd);
            add_log(temp.book_name);
            add_log("has been issued to ");
            add_log(person_name);
            add_log("\n");
            return true;
        }
    }
    // printf("Book Issue Failed2\n");
    add_log("Book Issue Failed2\n");
    close(fd);
    return false;
}
bool return_book(int isbn)
{
    int fd = open("book_details.txt",O_RDWR);
    if(fd==-1)
    {
        // printf("Book Return Failed\n");
        add_log("Book Return Failed\n");
        return false;
    }
    Book temp;
    while(read(fd,&temp,sizeof(temp)))
    {
        if(temp.isbn==isbn)
        {
            struct flock wrlk;
            wrlk.l_type=F_WRLCK;
            wrlk.l_whence=lseek(fd,0,SEEK_CUR)-sizeof(temp);
            wrlk.l_start=0;
            wrlk.l_len=sizeof(temp);
            wrlk.l_pid=getpid();
            fcntl(fd,F_SETLKW,&wrlk);
            temp.quantity++;
            lseek(fd,-sizeof(temp),SEEK_CUR);
            write(fd,&temp,sizeof(temp));
            wrlk.l_type=F_UNLCK;
            fcntl(fd,F_SETLK,&wrlk);
            close(fd);
            add_log(temp.book_name);
            add_log("was returned\n");
            return true;
        }
    }
    // printf("Book Return Failed\n");
    add_log("Book Return Failed\n");
    close(fd);
    return false;
}
