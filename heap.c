#include "heap.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define INITIAL_HEAP_CAPACITY 16

typedef int templ; 

typedef struct Heap {
    templ* elements;
    int size;
    int capacity;
} Heap;

Heap heap_create();
void heap_insert(Heap *heap, templ value);
void heap_remove(Heap *heap);
void heap_resize(Heap *heap);

void heap_print(Heap heap) {
    for (int i = 0; i < heap.size; i++) {
        printf("%d ", heap.elements[i]);
    }

    printf("\n");
}

bool array_equal(void *a, size_t a_size, void *b, size_t b_size) {
    return a_size == b_size && memcmp(a, b, a_size) == 0;
}

bool is_heap(Heap heap) {
    for (int i = 0; i < heap.size; i++) {
        int left_child = (i * 2) + 1;
        int right_child = (i * 2) + 2;

        if (left_child < heap.size && heap.elements[left_child] > heap.elements[i]) {
            return false;
        }
        
        if (right_child < heap.size && heap.elements[right_child] > heap.elements[i]) {
            return false;
        }
    }
    return true;
}

void test1() {
    printf("Can insert an element\n");

    Heap heap = heap_create(); 
    heap_insert(&heap, 0);
    
    int result[] = {0};
    assert(array_equal(heap.elements, heap.size * sizeof(templ), result, sizeof(result)));
    assert(is_heap(heap));
}

void test2() {
    printf("Can insert two elements\n");

    Heap heap = heap_create(); 
    heap_insert(&heap, 1);
    heap_insert(&heap, 0);
    
    int result[] = {1, 0};
    assert(array_equal(heap.elements, heap.size * sizeof(templ), result, sizeof(result)));
    assert(is_heap(heap));
}

void test3() {
    printf("Can insert an element that needs to be bubbled up\n");

    Heap heap = heap_create(); 
    heap_insert(&heap, 0);
    heap_insert(&heap, 1);
    
    int result[] = {1, 0};
    assert(array_equal(heap.elements, heap.size * sizeof(templ), result, sizeof(result)));
    assert(is_heap(heap));
}

void test4() {
    printf("Can handle a bunch of bubbling up\n");

    Heap heap = heap_create(); 
    heap_insert(&heap, 0);
    heap_insert(&heap, 1);
    heap_insert(&heap, 2);
    heap_insert(&heap, 3);
    heap_insert(&heap, 4);
    heap_insert(&heap, 7);
    heap_insert(&heap, 6);
    heap_insert(&heap, 19);
    
    int result[] = {19, 7, 6, 3, 2, 1, 4, 0};
    assert(array_equal(heap.elements, heap.size * sizeof(templ), result, sizeof(result)));
    assert(is_heap(heap));
}

void test5() {
    printf("Can handle a bunch of non bubbling up\n");

    Heap heap = heap_create(); 
    heap_insert(&heap, 20);
    heap_insert(&heap, 19);
    heap_insert(&heap, 18);
    heap_insert(&heap, 17);
    heap_insert(&heap, 16);
    heap_insert(&heap, 15);
    heap_insert(&heap, 14);
    heap_insert(&heap, 12);
    
    int result[] = {20, 19, 18, 17, 16, 15, 14, 12};
    assert(array_equal(heap.elements, heap.size * sizeof(templ), result, sizeof(result)));
    assert(is_heap(heap));
}

void test6() {
    printf("Can remove elements\n");

    Heap heap = heap_create(); 
    heap_insert(&heap, 0);  // 0
    heap_insert(&heap, 1);  // 1 0
    heap_insert(&heap, 2);  // 2 0 1
    heap_remove(&heap);     // 1 0
    heap_remove(&heap);     // 0
    heap_insert(&heap, 3);  // 3 0
    heap_insert(&heap, 4);  // 4 3 0
    heap_remove(&heap);     // 3 0
    heap_insert(&heap, 7);  // 7 3 0
    heap_insert(&heap, 6);  // 7 3 6 0
    heap_insert(&heap, 19); // 19 7 6 3 0
    heap_remove(&heap);     // 7 6 3 0
    
    int result[] = {7, 6, 3, 0};
    assert(array_equal(heap.elements, heap.size * sizeof(templ), result, sizeof(result)));
    assert(is_heap(heap));
}

void test7() {
    printf("Can resize to add many elements\n");

    Heap heap = heap_create(); 
    for (int i = 0; i < 100; i++) {
        heap_insert(&heap, i);  // 0
    }

    heap_print(heap);
    int result[] ={ 99, 93, 98, 76, 92, 97, 60, 67, 75, 83, 91, 96, 51, 55, 59, 62, 66, 70, 74, 78, 82, 86, 90, 94, 95, 48, 50, 28, 54, 56, 58, 31, 45, 63, 65, 35, 69, 71, 73, 39, 77, 79, 81, 43, 85, 87, 89, 47, 61, 46, 29, 5, 23, 22, 49, 4, 25, 12, 53, 11, 27, 26, 57, 0, 16, 9, 36, 6, 30, 21, 64, 3, 32, 15, 68, 14, 34, 33, 72, 2, 20, 17, 44, 8, 38, 37, 80, 7, 40, 19, 84, 18, 42, 41, 88, 1, 24, 13, 52, 10 };
    assert(array_equal(heap.elements, heap.size * sizeof(templ), result, sizeof(result)));
    assert(is_heap(heap));
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
}

Heap heap_create() {
    Heap heap;

    heap.elements = malloc(INITIAL_HEAP_CAPACITY * sizeof(templ));
    heap.capacity = INITIAL_HEAP_CAPACITY;
    heap.size = 0;

    return heap;
}

void heap_insert(Heap *heap, templ value) {
    if (heap->size >= heap->capacity) {
        heap_resize(heap);
    }

    int current_index = heap->size;
    int parent_index = (heap->size - 1) / 2;
    while (current_index > 0 && value > heap->elements[parent_index]) {
        heap->elements[current_index] = heap->elements[parent_index];

        current_index = parent_index;
        parent_index = (parent_index - 1) / 2;
    }
    heap->elements[current_index] = value;
    heap->size++;
}

void heap_remove(Heap *heap) {
    assert(heap->size > 0);

    int position = 0;
    while (true) {
        int left_child = (position * 2) + 1;
        int right_child = (position * 2) + 2;
        
        int greater_child = -1;
        if (right_child < heap->size && heap->elements[right_child] > heap->elements[left_child]) {
            greater_child = right_child;
        } else if (left_child < heap->size) {
            greater_child = left_child;
        }

        if (greater_child == -1) {
            break;
        }

        heap->elements[position] = heap->elements[greater_child];
        position = greater_child;
    }
    heap->size--;
}

void heap_resize(Heap *heap) {
    int new_capacity = heap->capacity * 2;
    int new_size = new_capacity * sizeof(templ);

    templ *new_memory = realloc(heap->elements, new_size);
    if (new_memory != NULL) {
        heap->capacity = new_capacity;
        return;
    }

    new_memory = malloc(new_capacity);
    memcpy(heap->elements, new_memory, heap->size * sizeof(templ));
    heap->capacity = new_capacity;
}

