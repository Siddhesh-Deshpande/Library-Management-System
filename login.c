#include"header.h"
#include"person.h"
bool check_user(char *username,char *password)
{
    int fd = open("user_details.txt",O_RDONLY);
    if(fd==-1)
    {
        return false;
    }
    Person temp;
    while(read(fd,&temp,sizeof(temp)))
    {
        if(strcmp(temp.name,username)==0 && strcmp(temp.password,password)==0)
        {
            close(fd);
            return true;
        }
    }
    close(fd);
    return false;
}
int login_user(char *username,char *password,int choice)
{
    if(choice==1)
    {
        if(check_user(username,password))
        {
            printf("Login trueful\n");
            add_log(username);
            add_log(" logged in truefully\n");
            return true;
        }
        else
        {
            printf("Login Failed\n");
            add_log(username);
            add_log(" failed to login\n");
            return false;

        }
    }
    else if(choice==2)
    {
        if(strcmp(username,"admin")==0 && strcmp(password,"admin")==0)
        {
            printf("Login trueful\n");
            add_log(username);
            add_log(" logged in truefully\n");
            return true;
        }
        else
        {
            printf("Login Failed\n");
            add_log(username);
            add_log(" failed to login\n");
            return false;
        }
    }
    else if(choice!=-1)
    {
        printf("Invalid Choice\n");
        add_log("Invalid Choice\n");
        return false;
    }
    else
    {
        return -1;
    }
}