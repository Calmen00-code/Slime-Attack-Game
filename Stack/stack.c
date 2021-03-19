#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

LinkedList* createStack()
{
    LinkedList *stack = createLinkedList();
    return stack;
}

void push( LinkedList *stack, void *data )
{
    insertStart( stack, data );
}

void* top( LinkedList *stack )
{
    void *data = NULL;
    data = peekLast( stack );
    return data;
}

void* pop( LinkedList *stack )
{
    void *data = NULL;
    data = removeLast(stack);
    return data;
}

void freeStack( LinkedList *stack )
{
    freeLinkedList(stack);
}
