#ifndef __STRUCTS_H__
#define __STRUCTS_H__

/* Global path assigned to the root's node */
#define ROOT "/"
/* Max input string length */
#define MAX_BUFFER 65535
/* Max path + value (arguments) string length */ 
#define MAX_ARGS 65529
/* Max command length */
#define MAX_COMMAND_LEN 6
/* MACRO to compare 2 strings */
#define equals(A,B) (!(hashing(A,B))
/* Verifies if stack's extreme are NULL */
#define EXT_PATH(extremes) (extremes->bottom->current->path)
/* Verifies if all components associated to root's node are NULL */
#define rootNULL(root) (root!= NULL && root->child==NULL && root->brother==NULL && root->parent==NULL)
/* Verifies if both current stack node and stack's extreme are NULL */
#define NULL_STACK(extremes, stack) (extremes->bottom!= NULL && extremes->bottom->current!= NULL && stack->current != NULL)
/* Verifies if  parent's associated pointers are NULL*/
#define CHECK_PARENT(current) (current != NULL && current->parent != NULL && current->parent->child != NULL)
/* (next 8 defines) Commands executed by the program*/
#define HELP_C "help"
#define QUIT_C "quit"
#define SET_C "set"
#define PRINT_C "print"
#define FIND_C "find"
#define LIST_C "list"
#define SEARCH_C "search"
#define DELETE_C "delete"

enum commands {HELP, QUIT, SET, PRINT, FIND, LIST, SEARCH, DELETE, NONE};

struct tree_node {
    char *path;
    char *value;
    int num_of_children;
    struct tree_node *parent;
    struct tree_node *brother;
    struct tree_node *child; 
};

struct stack_node{
    struct tree_node *current;
    struct stack_node *previous, *next;
};

struct stack {
    struct stack_node *bottom;
    struct stack_node *top;
};

#endif