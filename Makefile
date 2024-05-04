CC = gcc
CFLAGS = -pthread

all: server client

server: login.o checks.o admin.o user.o server.o
	$(CC) $(CFLAGS) $^ -o $@

client: client.o
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o server client
