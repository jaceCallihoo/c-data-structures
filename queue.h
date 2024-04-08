#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INITIAL_QUEUE_CAPACITY 16

#define DEFINE_QUEUE_HEADER(name, type) \
typedef struct name { \
    int size; \
    int capacity; \
    int head; \
    int tail; \
    type* elements; \
} name; \
\
name queue_##type##_create(); \
void queue_##type##_enqueue(name *q, type a); \
void queue_##type##_dequeue(name *q); \
type queue_##type##_peek(name q);

#define DEFINE_QUEUE(name, type) \
\
static void queue_##type##_resize(name *q) { \
    int new_capacity = q->capacity * 2; \
    type *new_memory = malloc(new_capacity * sizeof(type));  \
    for (int i = 0; i < q->size; i++) { \
        int old_index = (i + q->head) % q->capacity; \
        new_memory[i] = q->elements[old_index]; \
    } \
\
    q->head = 0; \
    q->tail = q->size; \
    q->capacity = new_capacity; \
    q->elements = new_memory; \
} \
\
name queue_##type##_create() { \
    name q; \
\
    q.size = 0; \
    q.capacity = INITIAL_QUEUE_CAPACITY; \
    q.elements = malloc(INITIAL_QUEUE_CAPACITY * sizeof(type)); \
    q.head = 0; \
    q.tail = 0; \
\
    return q; \
} \
\
void queue_##type##_enqueue(name *q, type a) { \
    if (q->size == q->capacity) { \
        queue_##type##_resize(q); \
    } \
\
    q->elements[q->tail] = a; \
    q->tail = (q->tail + 1) % q->capacity; \
    q->size++; \
} \
\
void queue_##type##_dequeue(name *q) { \
    assert(q->size != 0); \
    q->head = (q->head + 1) % q->capacity; \
    q->size--; \
} \
\
type queue_##type##_peek(name q) { \
    return q.elements[q.head];  \
} \

