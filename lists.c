#include "lists.h"
#include <stdio.h>
#include <stdlib.h>

void listInit (list *n, int initSize){
    n->used = 0;
    n->size = initSize;
    n->notes = malloc(initSize * sizeof(notes));
}

void addNote (list *n, notes element){
    if (n->used == n->size){
        n->size *= 2;
        n->notes = realloc(n->notes, n->size * sizeof(notes));
    }
    n->notes[n->used++] = element;
}

void removeNote (list *n){
    notes empty;
    n->used--;
    n->notes[n->used] = empty;
}

void freeList(list *n){
    free(n->notes);
    n->notes = NULL;
    n->used = n->size = 0;
}