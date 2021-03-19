CC = gcc
CFLAGS = -Werror -Wall -ansi -pedantic -g
OBJ = test.o stack.o LinkedList.o
EXEC = test

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

test.o : test.c stack.h
	$(CC) $(CFLAGS) -c test.c

stack.o : stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

LinkedList.o : LinkedList.c LinkedList.h
	$(CC) $(CFLAGS) -c LinkedList.c

clean: 
	rm -f $(OBJ) $(EXEC) 
