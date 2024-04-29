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
bool perform_unlock(int fd, struct flock *wrlk)
{
    wrlk->l_type=F_UNLCK;
    int status = fcntl(fd,F_SETLKW,wrlk);
    if(status==-1)
    {
        return false;
    }
    else
    {
        return true;
    }
}
bool perform_wlock(int fd , struct flock *wrlk)
{
    wrlk->l_type=F_WRLCK;
    wrlk->l_whence=SEEK_SET;
    wrlk->l_start=0;
    wrlk->l_len=0;
    wrlk->l_pid=getpid();
    int status = fcntl(fd,F_SETLKW,wrlk);
    if(status==-1)
    {
        return false;
    }
    else
    {
        return true;
    }
}
bool add_user(Person p)
{
    int fd = open("user_details.txt",O_RDWR|O_CREAT,0666);
    if(fd==-1)
    {
        add_log("User add failed\n");
        return false;
    }
    struct flock wrlk; // Performing file locking.
    perform_wlock(fd,&wrlk);
    //remove thiss
    // printf("Sleeping for testing\n");;
    // sleep(50);
    // remove this.
    int st1 = lseek(fd,0,SEEK_END);
    int st2 = write(fd,&p,sizeof(p));
    if(st1==-1 || st2==-1)
    {
        perform_unlock(fd,&wrlk);
        add_log("User add failed\n");
        return false;
    }
    add_log("New User ");
    add_log(p.name);
    add_log("has been added \n");
    perform_unlock(fd,&wrlk);//Unlocking the file.
    close(fd);
    return true;
}
bool add_book(Book b)
{
    int fd = open("book_details.txt",O_RDWR|O_CREAT,0666);
    if(fd==-1)
    {
        add_log("Book Add Failed\n");
        return false;
    }
    struct flock wrlk;
    perform_wlock(fd,&wrlk);
    //remove thiss
    // printf("Sleeping for testing\n");;
    // sleep(50);
    // remove this.
    int s1 = lseek(fd,0,SEEK_END);
    int s2= write(fd,&b,sizeof(b));
    if(s1==-1 || s2==-1)
    {
        perform_unlock(fd,&wrlk);
        add_log("Book Add Failed\n");
        return false;
    }
    add_log("New Book ");
    add_log(b.book_name);
    add_log("has been added\n");
    perform_unlock(fd,&wrlk);
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
            // read locking the specific record only.
            struct flock rdlk;
            rdlk.l_type=F_RDLCK;
            rdlk.l_whence=lseek(fd,0,SEEK_CUR)-sizeof(temp);
            rdlk.l_start=0;
            rdlk.l_len=sizeof(temp);
            rdlk.l_pid=getpid();
            fcntl(fd,F_SETLKW,&rdlk);
            *b=temp;
            close(fd);
            add_log("Details of ");
            add_log(temp.book_name);
            add_log("were obtained successfully\n");
            perform_unlock(fd,&rdlk);
            return;
        }
    }
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
            //Write locking the specific record only.   
            struct flock wrlk;
            wrlk.l_type=F_WRLCK;
            wrlk.l_whence=lseek(fd,0,SEEK_CUR)-sizeof(temp);
            wrlk.l_start=0;
            wrlk.l_len=sizeof(temp);
            wrlk.l_pid=getpid();
            fcntl(fd,F_SETLKW,&wrlk);
            temp.quantity=newval;
            lseek(fd,-sizeof(temp),SEEK_CUR);
            write(fd,&temp,sizeof(temp));
            perform_unlock(fd,&wrlk);
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
