#ifndef __PUBLIC_H__
#define __PUBLIC_H__

typedef struct tree_node* tree_node_s;
typedef struct stack_node* stack_node_s;
typedef struct stack* stack_s;

/* Error message 1*/
#define NOT_FOUND "not found\n"
/* Error message 2*/
#define NO_DATA "no data\n"
/* Error message 3 */
#define NO_MEMORY "No memory.\n"
/* help message - help command */
#define HELP_MESSAGE "help: Imprime os comandos disponíveis."
/* help message - quit command */
#define QUIT_MESSAGE "quit: Termina o programa."
/* help message - set command */
#define SET_MESSAGE "set: Adiciona ou modifica o valor a armazenar."
/* help message - print command */
#define PRINT_MESSAGE "print: Imprime todos os caminhos e valores."
/* help message - find command */
#define FIND_MESSAGE "find: Imprime o valor armazenado."
/* help message - list command */
#define LIST_MESSAGE "list: Lista todos os componentes imediatos de um sub-caminho."
/* help message - search command */
#define SEARCH_MESSAGE "search: Procura o caminho dado um valor."
/* help message - delete command */
#define DELETE_MESSAGE "delete: Apaga um caminho e todos os subcaminhos."


/* main.c */
int chooseCommand(char buffer[]);
void readLine(char buffer[]);
int hashing(char str1[], char str2[]);
void clear(char string[]);
void clearArray(char string[]);
void helpFunction();
int quitFunction(tree_node_s root, stack_s extremes, char buffer[]);

/* tree.c */
tree_node_s treeConstructor();
tree_node_s newTreeNode();
void setNodePointers(tree_node_s node);
tree_node_s treeDestructor(tree_node_s node);
void nodeDestructor(tree_node_s node);
void treeAdd(tree_node_s root, char buffer[]);
tree_node_s auxAddTree(tree_node_s parent, char path[]);
tree_node_s newChild(char path[]);
tree_node_s brotherSearch(tree_node_s current, char path[]);
tree_node_s treeSearch(tree_node_s root, char buffer[], stack_node_s top, stack_s extremes);
void treeFind(tree_node_s root, char buffer[]);
stack_node_s treePrint(tree_node_s root, stack_node_s top, stack_s extremes);
void listRoot(tree_node_s root);
void treeList(tree_node_s root, char buffer[]);
tree_node_s nodeSearch(tree_node_s root, char buffer[]);
void treeDelete(tree_node_s root, char buffer[]);

/* stack.c*/
stack_s stackConstructor();
stack_node_s setStackNode();
void destroyStack(stack_node_s stack);
stack_node_s push(tree_node_s adding, stack_node_s stack, stack_s extremes);
stack_node_s pop(stack_node_s top);
int isEmpty(stack_node_s stack);
void printForList(stack_s extremes);
void printForPrint(stack_s extremes);
void verifyExtremes(stack_s extremes, stack_node_s stack);

/* sort-algorithms.c */
void exchange(tree_node_s sort[], int i, int j);
int less(tree_node_s first, tree_node_s second);
int partition(tree_node_s sort[], int l, int r);
void quicksort(tree_node_s sort[], int l, int r);
void selectionSort(tree_node_s sortList[], int max_size);

#endif