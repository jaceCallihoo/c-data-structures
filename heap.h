#ifndef HEAP_H
#define HEAP_H

#define INITIAL_HEAP_CAPACITY 16

typedef int templ; 

typedef struct Heap {
    templ* elements;
    int size;
    int capacity;
    int (*comp_func)(const void*, const void*);
} Heap;

Heap heap_create(int (*comp_func)(const void*, const void*));
void heap_insert(Heap *heap, templ value);
void heap_remove(Heap *heap);

#endif

