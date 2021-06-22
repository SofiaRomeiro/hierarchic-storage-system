/* 
* File: main.c
* Author: Sofia Romeiro, ist198968
* Description: A program to create an hierarchical memory file system.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"

/* Chooses which command will be executed based on user's input */
int main() {
    tree_node_s root = treeConstructor(); /* Root node */
    stack_node_s stack = NULL; /* pointer to the first stack node */
    stack_s extremes = stackConstructor(); /* stack's extreme */
    char buffer[MAX_BUFFER+1]; /* array to read from stdin */
    int command, quit=0;
    while (!quit) {
        buffer[0] = '\0';
        command = chooseCommand(buffer);
        switch (command) {
            case HELP:
                helpFunction();
                break;
            case QUIT:
                treeDelete(root, buffer);
                quit = quitFunction(root, extremes, buffer);
                break;            
            case SET:     
                treeAdd(root, buffer);
                break;            
            case PRINT:
                treePrint(root, stack, extremes);
                break;
            case FIND:
                treeFind(root, buffer);
                break;
            case LIST:
                treeList(root, buffer);
                break;
            case SEARCH:
                treeSearch(root, buffer, stack, extremes);
                break;            
            case DELETE:
                treeDelete(root, buffer);
                break;            
        }
    }    
    return 0;
}

/* Filters the input to determine which command was introduced by the user 
* Also separates the command from the rest of the input
* Returns the correspondent command ENUM number
*/
int chooseCommand(char buffer[]) {
    char *command=NULL, *array=NULL;
    char aux[MAX_BUFFER+1]; /* aux array to help separate the input*/
    aux[0]= '\0';    
    readLine(buffer); 
    if (equals(buffer, NO_MEMORY))) return QUIT;
    strcpy(aux, buffer);  
    command = strtok(aux, " \t");
    array = strtok(NULL, "\0");
    if (array!=NULL) strcpy(buffer, array);
    else buffer[0] = '\0';
    if (equals(command, HELP_C))) return HELP;
    else if (equals(command, QUIT_C))) return QUIT;
    else if (equals(command, SET_C))) return SET;
    else if (equals(command, PRINT_C)))  return PRINT;
    else if (equals(command, FIND_C))) return FIND;
    else if (equals(command, LIST_C))) return LIST;
    else if (equals(command, SEARCH_C))) return SEARCH;
    else if (equals(command, DELETE_C))) return DELETE;
    else return QUIT;
}

/* Reads an entire line from stdin */
void readLine(char buffer[]) {
    char c;
    int i=0;
    while ((c=getchar())!= '\n' && c != EOF) {
        if (i == MAX_BUFFER+2) {
            printf(NO_MEMORY);
            strcpy(buffer, NO_MEMORY);
            return;            
        }
        buffer[i++] = c;             
    }
    buffer[i] = '\0';
    return;
}

/* Filters the first arrays' char 
* Returns if "string" str1 is equal to "string" str2*/
int hashing(char str1[], char str2[]) {
    if (str1[0] != str2[0]) return 1;
    else return strcmp(str1, str2);
}

/* Sets the array */
void clear(char string[]) {
    string[0] = '\0';
}

/* Clears the entire array's memory */
void clearArray(char string[]) {
    memset(string, '\0', strlen(string));
}

/* prints all help command's instructions */
void helpFunction() {
    puts(HELP_MESSAGE);
    puts(QUIT_MESSAGE);
    puts(SET_MESSAGE);
    puts(PRINT_MESSAGE);
    puts(FIND_MESSAGE);
    puts(LIST_MESSAGE);
    puts(SEARCH_MESSAGE);
    puts(DELETE_MESSAGE);
}

/* Frees all memory still alocated 
* Returns 1, which means "True" to quit the program
*/
int quitFunction(tree_node_s root, stack_s extremes, char buffer[]) {
    nodeDestructor(root);
    free(extremes);
    clearArray(buffer);
    return 1;
}