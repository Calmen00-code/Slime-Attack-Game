#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define RESET "\033[0m" 
#define PASSED "\033[1;33m"
#define FAILED "\033[1;31m"
#define TOL 0.001

double ucp_abs( double result )
{
    double num = result;
    if( result <= 0 )
        num = result * -1;
    return num;
}
 
int main()
{
    LinkedList *stack = NULL;
    int iNum = 10, *iPtr = NULL;
    double dNum = 0.5, *dPtr = NULL;
    char str[] = "String", *strPtr = "";
    char ch = 'a', *chPtr = NULL;

    printf("===== Test Stack =====\n\n");

/* ------------------------------------------------- */

    printf("Create Stack: ");

    stack = createStack();

    if( stack == NULL )
        printf("%sFAILED%s\n", FAILED, RESET);
    else
        printf("%sPASSED%s\n", PASSED, RESET);

/* ---------------------------------------------------------------------------- */

    printf("\n===== Push stack =====\n");
    
    printf("\nInteger: ");

    push( stack, &iNum );
    if( *((int *)peekFirst(stack)) == 10 ) 
        printf("%sPASSED%s\n", PASSED, RESET);
    else 
    {
        printf("%sFAILED%s\n", FAILED, RESET);
        printf("Output at FAILED: %d\n\n", *((int*)top(stack)));
    }

    printf("Double: ");
    push( stack, &dNum );
    if( ucp_abs(*((double *)peekFirst(stack)) - 0.5) <= TOL )
        printf("%sPASSED%s\n", PASSED, RESET);
    else
    {
        printf("%sFAILED%s\n", FAILED, RESET);
        printf("Output at FAILED: %f\n\n", *((double*)top(stack)));
    }

    printf("String: ");
    push( stack, str );
    if( strcmp( (char *)peekFirst(stack), "String" ) == 0 )
        printf("%sPASSED%s\n", PASSED, RESET);
    else 
    {
        printf("%sFAILED%s\n", FAILED, RESET);
        printf("Output at FAILED: %s\n\n", (char*)top(stack));
    }

    printf("Character: ");
    push( stack, &ch );
    if( *((char *)peekFirst(stack)) == 'a' )
        printf("%sPASSED%s\n", PASSED, RESET);
    else
    {
        printf("%sFAILED%s\n", FAILED, RESET);
        printf("Output at FAILED: %c\n\n", *((char*)peekFirst(stack)));
    }

    printf("Count Push: ");
    if( stack->count == 4 )
        printf("%sPASSED%s\n", PASSED, RESET);
    else
    {
        printf("%sFAILED%s\n", FAILED, RESET);
        printf("Output at FAILED: %d\n\n", stack->count);
    }

/* ---------------------------------------------------------------------------- */

    printf("\n===== Pop stack =====\n");

    printf("\nInteger: ");
    iPtr = (int *)pop(stack);
    if( *iPtr == 10 )
        printf("%sPASSED%s\n", PASSED, RESET);
    else
    {
        printf("%sFAILED%s\n", FAILED, RESET);
        printf("Output at FAILED: %d\n\n", *iPtr);
    }

    printf("Double: ");
    dPtr = (double *)pop(stack);
    if( ucp_abs(*dPtr - 0.5) <= TOL )
        printf("%sPASSED%s\n", PASSED, RESET);
    else
    {
        printf("%sFAILED%s\n", FAILED, RESET);
        printf("Output at FAILED: %f\n\n", *dPtr);
    }

    printf("String: ");
    strPtr = (char *)pop(stack);
    if( strcmp( strPtr, "String") == 0 )
        printf("%sPASSED%s\n", PASSED, RESET);
    else
    {
        printf("%sFAILED%s\n", FAILED, RESET);
        printf("Output at FAILED: %s\n\n", strPtr);
    }

    printf("Character: ");
    chPtr = (char *)pop(stack);
    if( *chPtr == 'a' )
        printf("%sPASSED%s\n", PASSED, RESET);
    else
    {
        printf("%sFAILED%s\n", FAILED, RESET);
        printf("Output at FAILED: %c\n\n", *chPtr);
    }

    printf("Count Pop: ");
    if( stack->count == 0 )
        printf("%sPASSED%s\n", PASSED, RESET);
    else
    {
        printf("%sFAILED%s\n", FAILED, RESET);
        printf("Output at FAILED: %d\n\n", stack->count);
    }

    printf("\n===== Test Completed =====\n");

    free(stack);
    stack = NULL;
    
    return 0;
}

