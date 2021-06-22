/* 
* File: sort-algorithms.c
* Author: Sofia Romeiro, ist198968
* Description: Two famous sorting algoritms adapted to vectors containing 
* arrays' pointers.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"

/* *************************  QUICK SORT ************************* */

/* Swaps two array's members positions */ 
void exchange(tree_node_s sort[], int i, int j) {
	tree_node_s aux;
	aux = sort[i];
	sort[i] = sort[j];
	sort[j] = aux; 
}

/* Compares two "strings"
*  Returns if the "first" one is less than the "second"
*/
int less(tree_node_s first, tree_node_s second) {
 	return 1 ? (strcmp(first->path,second->path)<0) : 0;
}

/* Partition for the quicksort algorithm
*  Returns the index before the values are less than the pivot's values
*/
int partition(tree_node_s sort[], int l, int r) {
	int i = l-1; 
	int j = r; 
	tree_node_s aux;
	aux = sort[r]; 
	while (i < j) { 				
		while (less(sort[++i], aux));				
		while (less(aux, sort[--j])) 
			if (j == l) break;
		if (i < j) exchange(sort, i, j); 
	}
	exchange(sort, r, i);
	return i; 
}

/* Adapted Quicksort algorithm, sorts an array by alphabet */
void quicksort(tree_node_s sort[], int l, int r) {
	int i;
	if (r <= l) return;
	i = partition(sort, l, r);
	quicksort(sort, l, i-1);
	quicksort(sort, i+1, r);
}

/* *************************  SELECTION SORT ************************* */

/* Adapted Selection sort algorithm, sorts an array by alphabet */
void selectionSort(tree_node_s sortList[], int max_size) {
    int i, j, min;
    for (i = 0; i < max_size; i++) {
        min = i;
        for (j = i+1; j < max_size; j++) {
            if (less(sortList[j],sortList[min])) min = j;
        }
        exchange(sortList, min, i);
    }
}

