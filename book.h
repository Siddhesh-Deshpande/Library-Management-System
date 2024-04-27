#ifndef BOOK_H
#define BOOK_H
typedef struct book{
    char book_name[100];
    char author_name[100];
    int isbn;
    int quantity;
} Book;
#endif