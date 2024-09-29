Library Management System - This is a library management system built on client server architecture where client can handle requests from multiple clients . Client can login in two forms either as a user or as a admin and perform the following operations:
1. User Mode- The client can login using the credetials of the user and then issue a book return a book . A user is allowed to issue only one copy of a particular book.
2. Admin Mode - The client can login using the admin credentials and admin can add a new book, modify the quantity of a given book,add a new user and retrieve details of a specific book (name of book,author name, isbn, quantity)

Specifications of The System-
1. Used Multithreading to build a concurrent server that can handle the request of multiple client at the same time.
2. Used Socket Programming to Communicate betweenn the client and the server.
3. Used file locking to prevent the race condition so that the data is updated correctly when multiple clients access the same file or the record. used both write as well as read locks for better performance in case two clients want to read the same file or record.

Steps to run the project - 
1. Clone the github repository.
2. Open the terminal in the folder that was downloaded.
3. Run the Command make clean.
4. Run the Command ./server
5. Run the command ./client in another terminal. Open as many terminals as you want the clients and run the ./client command . 
Perform the respective operations that you want to and check the result you will be able to see that even if multiple clients are  perrfoming operation simultaneously still the values are updated correctly.

Note - Since it is practically difficult to see the race conditions the user if wished can put the getchar command before the unlock operation and see in another client is able to perform the same operation . This suggested change can be done in the admin.c and client.c files before the unlock operation happens in this way user will observe that it has to wait untill the lock is released by pressing an enter. alternative way can be to use sleep to see the race but may be time consuming .

Concepts used - Multithreading,File Locking,IPC,FIle I/O
