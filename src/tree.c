/* 
* File: tree.c
* Author: Sofia Romeiro, ist198968
* Description: The hole process envolving a m-way tree, since construction 
* to operations like search and find and, at the end, the self destruction.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"

/* Sets the first tree node 
*  Returns the root's node pointer
*/
tree_node_s treeConstructor(){
    tree_node_s new_tree = (tree_node_s)malloc(sizeof(struct tree_node));    
    new_tree->path = (char *)malloc(sizeof(char)*strlen(ROOT)+1);
    new_tree->path[0] = '\0';
    strcpy(new_tree->path, ROOT);
    setNodePointers(new_tree);
    return new_tree;
}

/* Creates a new tree node
*  Returns the created node pointer 
*/
tree_node_s newTreeNode() {
    tree_node_s new_node = (tree_node_s) malloc(sizeof(struct tree_node));
    new_node->path = NULL;
    setNodePointers(new_node);
    return new_node;
}

/* Creates a new child node 
*  Returns new node's pointer
*/
tree_node_s newChild(char path[]) {
    tree_node_s newchild;
    newchild = newTreeNode();
    newchild->path = (char *) malloc(sizeof(char) * (strlen(path)+1));
    newchild->path[0] = '\0';
    strcpy(newchild->path, path);
    return newchild;
}

/* Initializes all node's pointers except the path's pointer
*/
void setNodePointers(tree_node_s node) {
    node->value = NULL;
    node->child = NULL;
    node->brother = NULL;   
    node->parent = NULL;
    node->num_of_children = 0;
    return;
}

/* Recursive function to free all memory allocated 
*  by a specific node and their children
*  Returns NULL when the entire memory envolved is free
*/
tree_node_s treeDestructor(tree_node_s node) {
    tree_node_s aux;
    if (node == NULL) return NULL;
    else if (rootNULL(node) && !equals(node->path, ROOT))) {
        nodeDestructor(node);
        return NULL;
    }
    if (node->child != NULL) return treeDestructor(node->child);
    else {
        if (node->brother != NULL) {
            node->parent->child = node->brother;
            aux = node->brother;
            node->brother=NULL;
            node->child=NULL;
            nodeDestructor(node);
            return treeDestructor(aux);
        } 
        else {
            if (node->parent != NULL) {
                node->parent->child = NULL;
                aux = node->parent;
                if (node->child == NULL && node->brother == NULL) {
                    nodeDestructor(node);
                }
                return treeDestructor(aux);
            }        
        }         
    }
    return NULL;
}

/* Frees all node's components */
void nodeDestructor(tree_node_s node) {
    free(node->path);
    free(node->value);
    free(node);
}

/* Adds or modifies a new node */
void treeAdd(tree_node_s root, char buffer[]) {  
    tree_node_s parent = root, current=NULL;
    char path[MAX_ARGS+1], value[MAX_ARGS+1],*path_p=NULL, *directory=NULL;
    path[0] = '\0';
    value[0] = '\0';  
    path_p = strtok(buffer, " \t");
    strcpy(path, path_p);
    path_p = strtok(NULL, "\0");
    strcpy(value, path_p);
    directory = strtok(path, "/");
    current = auxAddTree(parent, directory);
    current->parent = parent;
    parent = current;
    while (directory != NULL) {
        directory = strtok(NULL, "/");
        if (directory==NULL) break;
        current = auxAddTree(parent, directory);
        current->parent = parent;
        parent = current;
    }
    current->value = (char *) malloc(sizeof(char)*(strlen(value)+1)); 
    current->value[0] = '\0'; 
    strcpy(current->value, value);
    clear(value);
    clear(path);  
}

/* Auxiliar function to create a new node
*  Returns new node's pointer 
*/
tree_node_s auxAddTree(tree_node_s parent, char path[]) {
    tree_node_s child, brother;
    if (parent->child != NULL) {      
        brother = brotherSearch(parent->child, path);
        if (brother != NULL) return brother;          
        else { 
            brother = brotherSearch(parent->child, NULL);
            child = newChild(path);
            child->parent = parent;
            parent->num_of_children += 1;
            brother->brother = child;
            return child;
        }
    }
    else {
        child = newChild(path);
        child->parent = parent;
        parent->num_of_children += 1;
        parent->child = child;
        return child;
    }
}

/* If the path is NULL: searches for the last brother created
*  Else: searches if the "path's name" exists as a brother node
*  Returns the asked node
*/
tree_node_s brotherSearch(tree_node_s current, char path[]) {
    tree_node_s aux = current;
    if (path == NULL) {
        while (aux->brother != NULL) aux = aux->brother;
        return aux;
    }
    else {
        while (aux != NULL) {
            if (equals(aux->path, path))) return aux;
            aux = aux->brother;
        }
    }
    return NULL;
}

/* Recursive function to search the value's path
*  Prints the path if it was found else raises error
*  Returns NULL when found or when there's an error
*/
tree_node_s treeSearch(tree_node_s root, char buffer[], stack_node_s top, stack_s extremes) {
    tree_node_s current = root, aux;
    stack_node_s stack = top; 
    if (current == NULL) { 
        printf(NOT_FOUND);       
        return NULL;
    }
    if (current->value != NULL && equals(current->value, buffer))) {   
        printForList(extremes);
        destroyStack(stack);
        return NULL;
    } 
    else if (current->child != NULL) {              
        stack = push(current->child, stack, extremes);        
        return treeSearch(current->child, buffer, stack, extremes);
    }
    else if (current->brother != NULL) {
        verifyExtremes(extremes, stack); 
        stack = pop(stack);          
        stack = push(current->brother,stack, extremes);
        return treeSearch(current->brother, buffer, stack, extremes);
    }
    else {
        if (current->parent!= NULL && current->parent->brother == NULL) {       
            aux = current;
            while (aux->parent != NULL) {
                if (aux->brother != NULL) {
                    verifyExtremes(extremes, stack);
                    stack = pop(stack);                    
                    stack = push(aux->brother, stack, extremes);
                    return treeSearch(aux->brother, buffer, stack, extremes);
                }
                else if (equals(aux->path, "/"))) {
                    verifyExtremes(extremes, stack);
                    stack = pop(stack);
                    return treeSearch(aux, buffer, stack, extremes);
                }                 
                aux = aux->parent;
                stack = pop(stack);
            }
        }
        else if (current->parent== NULL) {
            printf(NOT_FOUND);
            return NULL;
        }            
        else {      
            verifyExtremes(extremes, stack);
            stack = pop(stack); 
            verifyExtremes(extremes, stack);
            stack = pop(stack);
            stack = push(current->parent->brother, stack, extremes);
            return treeSearch(current->parent->brother, buffer, stack, extremes);
        }
    }   
    printf(NOT_FOUND);
    return NULL; 
} 

/* Finds the stored value by the given path
*  Prints the value if it was found, else raises error
*  Returns Returns NULL when found or when there's an error
*/
void treeFind(tree_node_s root, char buffer[]) {    
    tree_node_s current = root;
    char *array;  
    array = strtok(buffer, "/"); 
    current = current->child;
    current = brotherSearch(current, array);
    while (array != NULL) {     
        if (current == NULL) {
            printf(NOT_FOUND);
            return;
        }  
        array = strtok(NULL, "/"); 
        if (array==NULL) break; 
        current = current->child;
        current = brotherSearch(current, array); 
    }    
    if (current->value == NULL) {
        printf(NO_DATA);
        return;
    }
    else {
        printf("%s\n", current->value);
        return;
    }
}

/* Recursive function to print all paths with associated values
*  Returns NULL when the task is concluded
*/
stack_node_s treePrint(tree_node_s root, stack_node_s top, stack_s extremes) {
    tree_node_s current = root;
    stack_node_s stack = top;
    if (rootNULL(root) && equals(root->path, "/"))) return NULL;
    if (current == NULL) return NULL; 
    if (current->value != NULL)  printForPrint(extremes);   
    if (current->child != NULL) {
        stack = push(current->child, stack, extremes);
        return treePrint(current->child, stack, extremes);
    } 
    else {
        if (current->brother != NULL) {
            verifyExtremes(extremes, stack); 
            stack = pop(stack);
            stack = push(current->brother, stack, extremes);
            return treePrint(current->brother, stack, extremes);
        }
        else {
            if (current->parent != NULL && current->parent->brother != NULL) {
                verifyExtremes(extremes, stack); 
                stack = pop(stack);
                verifyExtremes(extremes, stack);   
                stack = pop(stack);
                stack = push(current->parent->brother, stack, extremes);
                return treePrint(current->parent->brother, stack, extremes); 
            }           
            else { 
                while (current->brother == NULL) { 
                    current = current->parent; 
                    if (current != NULL && equals(current->path, "/"))) {                      
                        destroyStack(stack);
                        return NULL;
                    }                      
                    stack = pop(stack);
                    verifyExtremes(extremes, stack);  
                }
                verifyExtremes(extremes, stack);
                stack = pop(stack); 
                if (current->brother == NULL) {
                    destroyStack(stack);
                    return NULL;
                }
                stack = push(current->brother, stack, extremes);
                return treePrint(current->brother, stack, extremes);               
            }
        }
    }
    return NULL;
}

/* Chooses which sort method will be used to sort by alphabet
*  Also prints the path's names sorted 
*/
void listRoot(tree_node_s root) {
    int num_of_nodes, i;
    tree_node_s aux = root->child, *sortList; 
    num_of_nodes = root->num_of_children;
    sortList = malloc(sizeof(struct tree_node) * num_of_nodes);
    for (i=0; i < num_of_nodes && aux != NULL; i++, aux = aux->brother) {
        sortList[i] = NULL;
        sortList[i] = aux;
    }
    if (num_of_nodes<5) selectionSort(sortList, num_of_nodes);
    else quicksort(sortList, 0, num_of_nodes-1);
    for (i=0; i < num_of_nodes; i++) printf("%s\n", sortList[i]->path);
    free(sortList);        
}

/* Lists all direct children from the given node */
void treeList(tree_node_s root, char buffer[]) {
    tree_node_s aux;
    if (strlen(buffer) == 0) {
        if (root->child == NULL) return;
        listRoot(root);
    }
    else {
        if (root->child == NULL) return;
        aux = nodeSearch(root, buffer);
        if (aux==NULL) {
            printf(NOT_FOUND);
            return;
        }
        listRoot(aux);
    }
}

/* Searches for a specific node according to the input
*  Returns the asked node
*/
tree_node_s nodeSearch(tree_node_s root, char buffer[]) {
    tree_node_s current = root; 
    char *array=NULL;  
    array = strtok(buffer, "/");
    current = current->child;
    current = brotherSearch(current, array);
    while (array != NULL) {
        if (current==NULL) return current;        
        array = strtok(NULL, "/");
        if (array == NULL) break;
        current = current->child;        
        current = brotherSearch(current, array);      
    }
    return current;
} 

/* Decides which node (and their children) will be deleted */
void treeDelete(tree_node_s root, char buffer[]) {
    tree_node_s current=root, finder, parent;
    char *array=NULL;
    if (strlen(buffer) == 0) {
        treeDestructor(root);
        return;
    }
    else {
        array = strtok(buffer, "/"); 
        while (array != NULL) {
            current = current->child;  
            current = brotherSearch(current, array);          
            if (current == NULL) {
                printf(NOT_FOUND);
                return;
            }   
            if (current->child == NULL) break;    
            array = strtok(NULL, "/");             
        }
        if (CHECK_PARENT(current) && 
            equals(current->parent->child->path, current->path))) {
            if (current->brother != NULL) {
                current->parent->child = current->brother;
                current->parent->num_of_children -= 1;
                current->brother = NULL;
            }
            else {
                current->parent->num_of_children -= 1;
                current->parent->child = NULL;
            }
        }
        else if (current != NULL) {
            parent = current->parent;
            finder = parent->child;
            while (finder->brother != NULL && 
                !equals(finder->brother->path, current->path))) {
                finder = finder->brother;
            }
            finder->brother = current->brother;
            parent->num_of_children -= 1;
            current->brother = NULL;
        }
        current->parent = NULL;      
        treeDestructor(current);
        return;     
    }
}
