#include "heap.h"

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

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
        heap_insert(&heap, i);
    }

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

