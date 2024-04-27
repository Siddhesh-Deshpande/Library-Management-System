#include "header.h"
#include "person.h"
#include "book.h"
Person make_person(char *username, char *password)
{
    Person p;
    strcpy(p.name, username);
    strcpy(p.password, password);
    return p;
}
Book make_book(char *book_name,char*author_name,int isbn,int quantity)
{
    Book b;
    strcpy(b.author_name,author_name);
    strcpy(b.book_name,book_name);
    b.isbn=isbn;
    b.quantity=quantity;
    return b;
}
void main()
{
    struct sockaddr_in serv;
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv.sin_port = htons(5555);
    connect(sd, (struct sockaddr *)&serv, sizeof(serv));
    while (1)
    {
        int choice;
        printf("Press 1 to Enter as normal user and 2 for admin user and press -1 to exit \n");
        scanf("%d", &choice);
        write(sd, &choice, sizeof(choice));
        if(choice==-1)
        {
            close(sd);
            break;
        }
        char username[100], password[100];
        printf("Enter Your Username:\n");
        scanf("%s", username);
        // username[strcspn(username, "\n")] = '\0';
        printf("Enter Your Password:\n");
        scanf("%s", password);
        write(sd, username, sizeof(username));
        write(sd, password, sizeof(password));
        int attempt_status;
        read(sd, &attempt_status, sizeof(attempt_status));
        if (attempt_status == -1)
        {
            close(sd);
            break;                        // to exit the program
        }
        else if (attempt_status == false) // login failed
        {
            printf("Login Failed\n");
        }
        else // login successs
        {
            if (choice == 1) // normal user
            {
                int option;
                printf("Press 3 to issue book and 4 to return book\n");
                scanf("%d", &option);
                write(sd, &option, sizeof(option));
                if (option == 3)
                {
                    int isbn;
                    printf("Enter ISBN of the book you want to issue\n");
                    scanf("%d", &isbn);
                    write(sd, &isbn, sizeof(isbn));
                    read(sd, &attempt_status, sizeof(attempt_status));
                    if (attempt_status)
                    {
                        printf("Book Issued\n");
                    }
                    else
                    {
                        printf("Book Issue Failed\n");
                    }
                }
                else if (option == 4)
                {
                    int isbn;
                    printf("Enter ISBN of the book you want to return \n");
                    scanf("%d", &isbn);
                    write(sd, &isbn, sizeof(isbn));
                    read(sd, &attempt_status, sizeof(attempt_status));
                    if (attempt_status)
                    {
                        printf("Book retturned successfully\n");
                    }
                    else
                    {
                        printf("Book return Failed\n");
                    }
                }
                else
                {
                    printf("Invalid Option\n");
                }
            }
            else if (choice == 2) // admin user
            {
                int option;
                printf("Press 1 to add user, 2 to add book, 5 to get book details and 6 to modify book details\n");
                scanf("%d", &option);
                write(sd, &option, sizeof(option));
                if (option == 1)
                {
                    char name[100], password[100];
                    printf("Enter the name of the user\n");
                    scanf("\n%[^\n]s", name);
                    name[strcspn(name, "\n")] = '\0';
                    printf("Enter the password of the user\n");
                    scanf("%s", password);
                    Person p = make_person(name, password);
                    write(sd, &p, sizeof(p));
                    read(sd, &attempt_status, sizeof(attempt_status));
                    if (attempt_status)
                    {
                        printf("User Added\n");
                    }
                    else
                    {
                        printf("User Add Failed\n");
                    }
                }
                else if (option == 2)
                {
                    char book_name[100], author_name[100];
                    int isbn, quantity;
                    printf("Enter the name of the book\n");
                    scanf("\n%[^\n]s", book_name);
                    book_name[strcspn(book_name, "\n")] = '\0';
                    printf("Enter the author of the book\n");
                    scanf("\n%[^\n]s", author_name);
                    author_name[strcspn(author_name, "\n")] = '\0';
                    printf("Enter the isbn of the book\n");
                    scanf("%d", &isbn);
                    printf("Enter the quantity of the book\n");
                    scanf("%d", &quantity);
                    Book b = make_book(book_name, author_name, isbn, quantity);
                    write(sd, &b, sizeof(b));
                    read(sd, &attempt_status, sizeof(attempt_status));  
                    if (attempt_status)
                    {
                        printf("Book Added\n");
                    }
                    else
                    {
                        printf("Book Add Failed\n");
                    }
                }
                else if(option== 5)
                {
                    int isbn;
                    scanf("%d",&isbn);
                    write(sd,&isbn,sizeof(isbn));
                    Book b;
                    read(sd,&b,sizeof(b));
                    if(b.isbn==-1)
                    {
                        printf("Book not found\n");
                    }
                    else
                    {
                        printf("Book Name: %s\n",b.book_name);
                        printf("Author Name: %s\n",b.author_name);
                        printf("ISBN: %d\n",b.isbn);
                        printf("Quantity: %d\n",b.quantity);
                    }
                }
                else if(option == 6)
                {
                    int isbn;
                    printf("Enter the ISBN of the book you want to modify\n");
                    scanf("%d",&isbn);
                    int newval; 
                    printf("Enter the new quantity of the book\n");
                    scanf("%d",&newval);
                    write(sd,&isbn,sizeof(isbn));
                    write(sd,&newval,sizeof(newval));
                    read(sd,&attempt_status,sizeof(attempt_status));
                    if(attempt_status)
                    {
                        printf("Book modified successfully\n");
                    }
                    else
                    {
                        printf("Book modification failed\n");
                    }    
                }
            }
        }
    }
}