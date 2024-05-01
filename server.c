#include "header.h"
#include "person.h"
#include "book.h"
#include "user.h"
#include "admin.h"
void *handle_client(void *arg)
{
    int client_sd = *(int*)arg;
    while(1)
    {
        int choice;
        char username[100],password[100];
        read(client_sd,&choice,sizeof(choice));
        read(client_sd,username,sizeof(username));
        read(client_sd,password,sizeof(password));
        int attempt_status = login_user(username,password,choice);
        write(client_sd,&attempt_status,sizeof(attempt_status)); //login checking completes here.
        if(attempt_status==-1)
        {
            printf("User %s logged out\n",username);
            close(client_sd);
            return NULL;
        }
        else if(attempt_status)
        {
            if(choice==1)
            {
                int option;
                read(client_sd,&option,sizeof(option));
                if(option==3)
                {
                    int isbn;
                    read(client_sd,&isbn,sizeof(isbn));
                    int x = issue_book(isbn,username);
                    write(client_sd,&x,sizeof(x));
                }
                else if(option==4)
                {
                    int isbn;
                    read(client_sd,&isbn,sizeof(isbn));
                    int x = return_book(isbn,username);
                    write(client_sd,&x,sizeof(x));                
                }
            }
            else if(choice==2)
            {
                int option;
                read(client_sd,&option,sizeof(option));
                if(option==1)
                {
                    Person p;
                    read(client_sd,&p,sizeof(p));
                    int x = add_user(p);
                    write(client_sd,&x,sizeof(x));  
                }
                else if(option==2)
                {
                    Book b;
                    read(client_sd,&b,sizeof(b));
                    int x = add_book(b);
                    write(client_sd,&x,sizeof(x));  
                }
                else if(option==5)
                {
                    int isbn;
                    read(client_sd,&isbn,sizeof(isbn));
                    Book b;b.isbn=-1;
                    get_book(&b,isbn);
                    write(client_sd,&b,sizeof(b));
                }
                else if(option==6)
                {
                    int isbn,quantity;
                    read(client_sd,&isbn,sizeof(isbn));
                    read(client_sd,&quantity,sizeof(quantity));
                    int x = modify_book(isbn,quantity);
                    write(client_sd,&x,sizeof(x));
                }
            }
        }
    }
    

}
void main()
{
    struct sockaddr_in server;
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5555);
    if(bind(sd, (struct sockaddr *)&server, sizeof(server))==-1)
    {
        perror("Bind failed");
        return;
    }
    if(listen(sd, 5)==-1)
    {
        perror("Listen failed");
        return;
    }
    while(1)
    {
        struct sockaddr_in client;
        int len = sizeof(client);
        int client_sd = accept(sd, (struct sockaddr *)&client, &len);
        printf("Client connected\n");
        if(client_sd==-1)
        {
            perror("Accept failed");
            return;
        }
        pthread_t thread;
        if(pthread_create(&thread,NULL,handle_client,&client_sd)==-1)
        {
            perror("Thread creation failed");
            return;
        }
        printf("thread now handles the client\n");
        pthread_detach(thread);
    }
}