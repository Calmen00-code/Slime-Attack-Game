CC = gcc
CFLAGS = -Werror -Wall -pedantic -ansi -g
OBJ = main.o LinkedList.o file.o newSleep.o stack.o display.o
EXEC = rpg

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c newSleep.h LinkedList.h file.h role.h display.h
	$(CC) $(CFLAGS) -c main.c

LinkedList.o : LinkedList.c LinkedList.h
	$(CC) $(CFLAGS) -c LinkedList.c

file.o : file.c file.h role.h stack.h
	$(CC) $(CFLAGS) -c file.c

newSleep.o : newSleep.c newSleep.h
	$(CC) $(CFLAGS) -c newSleep.c

stack.o : stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

display.o : display.c display.h role.h newSleep.h stack.h
	$(CC) $(CFLAGS) -c display.c

clean:
	rm -f $(EXEC) $(OBJ) 
