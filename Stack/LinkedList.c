#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

LinkedList* createLinkedList()
{
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    return list;
}

void insertStart( LinkedList *list, void *entry )
{
    LinkedListNode *newNd = NULL;

    /* Creating the node */
    newNd = (LinkedListNode *) malloc(sizeof(LinkedListNode));
    newNd->next = NULL;
    newNd->data = entry;

    if( list->head == NULL )    /* head = NULL indicates it is first node */
    {
        list->head = newNd;     /* current node will be the head node */
        list->tail = newNd;     /* tail is same too since list is empty */
    }
    else                        /* head != NULL indicates it is not first node */
    {
        newNd->next = list->head;  /* Connect newNd into the current head */
        list->head = newNd;        /* Update the head to be newNd */
    }
    list->count++;              /* Increase in node (insertion) */
}

void* removeStart( LinkedList *list )
{
    LinkedListNode *deleteNd = NULL;
    void *retData = NULL;

    if( list->head != NULL )    /* list must not be empty */
    {
        deleteNd = list->head;  /* get the address of head as it will be update */
        retData = deleteNd->data;
        list->head = list->head->next;  /* head is updated */
        
        free(deleteNd);         /* deleteNd is now removed */
        deleteNd = NULL;

        list->count--;          /* a node is removed */
    }
    return retData;
}

void insertLast(LinkedList *list, void *entry )
{
    LinkedListNode *newNd = NULL;
    LinkedListNode *travelNd = NULL;

    /* Creating the node */
    newNd = (LinkedListNode *) malloc(sizeof(LinkedListNode));
    newNd->next = NULL;
    newNd->data = entry;

    if( list->head == NULL )    /* head = NULL indicates it is first node */
    {
        list->head = newNd;     /* current node will be the head node */
        list->tail = newNd;     /* tail is same too since list is empty */
    }
    else
    {
        travelNd = list->head;  /* Traversal always start from head */

       /* ASSERTION: Traversing until tail was found  *
        *            (Tail next is pointing to NULL)  */
        while( travelNd->next != NULL )
            travelNd = travelNd->next;

        travelNd->next = newNd;
        list->tail = newNd;   /* newNd now becomes tail */
    }
    list->count++;  /* Increase in node (insertion) */
}

void* removeLast( LinkedList *list )
{
    LinkedListNode *travelNd = NULL;
    LinkedListNode *deleteNd = NULL;
    void *retData = NULL;

    if( list->head != NULL )    /* Only free list that is not empty */
    {
        travelNd = list->head;  /* Traversal always start from head */

        /* ASSERTION: Traverse until we get the node *
         *            that is pointing to tail       */
        while( travelNd->next != list->tail && list->head != list->tail )
            travelNd = travelNd->next;

        travelNd->next = NULL;  /* travelNd is now node before tail node so 
                                   disconnect current tail from list 
                                   (but not freed yet) */

        deleteNd = list->tail;  /* node to be deleted is tail */
        retData = list->tail->data; /* we will remove tail */

        list->tail = travelNd;  /* the latest tail will be 
                                   where travelNd stops */

        free(deleteNd);       /* old tail will be deleted */
        deleteNd = NULL;

        list->count--;          /* A node was removed */
    }
    return retData;
}

void* peekLast( LinkedList *list )
{
    void *retData = NULL;

    if( list->tail != NULL )
        retData = list->tail->data;
 
    return retData; 
}

void* peekFirst( LinkedList *list )
{
    void *retData = NULL;

    if( list->head != NULL )
        retData = list->head->data;

    return retData; 
}

void printLinkedList( LinkedList *list )
{

}

void freeLinkedList( LinkedList *list )
{
    LinkedListNode *delNd = NULL;

    delNd = list->head;
    while( delNd != NULL )
    {
        /* Only free those allocated data */
        if( delNd->data != NULL )
        {
            free(delNd->data);
            delNd->data = NULL;
        }

        list->head = delNd->next;

        free(delNd);
        delNd = NULL;

        delNd = list->head;
    }

    free(list);
    list = NULL;
}
