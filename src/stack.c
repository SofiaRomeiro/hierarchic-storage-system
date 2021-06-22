/* 
* File: stack.c
* Author: Sofia Romeiro, ist198968
* Description: The hole process envolving a stack, since construction 
* to operations like printing the content and, at the end, the self destruction.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"

/* Sets the stack  
*  Returns the created stack's pointer
*/
stack_s stackConstructor() {
    stack_s newstack = (stack_s) malloc(sizeof(struct stack));
    newstack->bottom = NULL;
    newstack->top = NULL;
    return newstack;
}

/* Creates a new stack node
*  Returns the created node's pointer
*/
stack_node_s setStackNode() {
    stack_node_s top = (stack_node_s) malloc(sizeof(struct stack_node));
    top->current = NULL;
    top->next = NULL;
    top->previous = NULL;
    return top;
}

/* Frees all memory allocated by the stack */
void destroyStack(stack_node_s stack) { 
    stack_node_s aux = stack;
    while (aux != NULL) aux = pop(aux);
    free(aux);
}

/* Adds a new node to the stack
*  Returns the new stack's top node pointer
*/
stack_node_s push(tree_node_s adding, stack_node_s stack, stack_s extremes) {
    if (isEmpty(stack)) {
        stack = setStackNode();
        stack->current = adding;
        extremes->bottom = stack;
        return stack;
    } 
    else {
        stack_node_s new = setStackNode();    
        new->current = adding;
        stack->previous = new;
        new->next = stack;
        if (extremes->bottom==NULL) extremes->bottom = new;
        return new;
    }  
}

/* Deletes a node from the stack
*  Returns the new stack's top node pointer
*/
stack_node_s pop(stack_node_s top) {
    stack_node_s old;
    if (!isEmpty(top)) {
        old = top;
        top = top->next;
        free(old);      
        return top;
    }
    else return NULL;
}

/* Checks if the stack is empty
*  Returns if is empty or not
*/
int isEmpty(stack_node_s stack) {
    return stack == NULL;
}

/* Prints the stack's content, asked by the List command */
void printForList(stack_s extremes) {  
    stack_node_s current= extremes->bottom;
    while(current != NULL) {
       printf("/%s", current->current->path);
       current = current->previous;
    }
    printf("\n");
}

/* Prints the stack's content, asked by the Print command */
void printForPrint(stack_s extremes) { 
    stack_node_s aux=NULL, current= extremes->bottom;
    while(current != NULL) {
       printf("/%s", current->current->path);
       aux = current;
       current = current->previous;
    }
    printf(" %s\n", aux->current->value);
}

/* Checks if there's need to change the stack's bottom pointer */
void verifyExtremes(stack_s extremes, stack_node_s stack) {
    if (NULL_STACK(extremes, stack) && 
		!hashing(EXT_PATH(extremes), stack->current->path)) {
        extremes->bottom = NULL;
    }
}
