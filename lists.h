#include <stddef.h>

typedef struct{
    double time;
	double freq;
	char ty;
}notes;

typedef struct{
    size_t used;
    size_t size;
    notes *notes;
}list;

void addNote (list *n, notes element);
void listInit (list *n, int initSize);
void removeNote (list *n);