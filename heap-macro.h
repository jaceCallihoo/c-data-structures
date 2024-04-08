#define INITIAL_HEAP_CAPACITY 16

#define DEFINE_HEAP_HEADER(name, type) \
typedef struct Heap { \
    type* elements; \
    int size; \
    int capacity; \
    int (*comp_func)(const void*, const void*); \
} Heap; \
\
Heap heap_create(int (*comp_func)(const void*, const void*)); \
void heap_insert(Heap *heap, type value); \
void heap_remove(Heap *heap); \

#define DEFINE_HEAP(name, type) \
static void heap_resize(Heap *heap) { \
    int new_capacity = heap->capacity * 2; \
    int new_size = new_capacity * sizeof(type); \
\
    type *new_memory = realloc(heap->elements, new_size); \
    if (new_memory != NULL) { \
        heap->capacity = new_capacity; \
        return; \
    } \
\
    new_memory = malloc(new_capacity); \
    memcpy(heap->elements, new_memory, heap->size * sizeof(type)); \
    heap->capacity = new_capacity; \
} \
\
Heap heap_create(int (*comp_func)(const void*, const void*)) { \
    Heap heap; \
\
    heap.elements = malloc(INITIAL_HEAP_CAPACITY * sizeof(type)); \
    heap.capacity = INITIAL_HEAP_CAPACITY; \
    heap.size = 0; \
    heap.comp_func = comp_func; \
\
    return heap; \
} \
\
void heap_insert(Heap *heap, type value) { \
    if (heap->size >= heap->capacity) { \
        heap_resize(heap); \
    } \
\
    int current_index = heap->size; \
    int parent_index = (heap->size - 1) / 2; \
    while (current_index > 0 && heap->comp_func(&value, &heap->elements[parent_index]) > 0) { \
        heap->elements[current_index] = heap->elements[parent_index]; \
\
        current_index = parent_index; \
        parent_index = (parent_index - 1) / 2; \
    } \
    heap->elements[current_index] = value; \
    heap->size++; \
} \
\
void heap_remove(Heap *heap) { \
    assert(heap->size > 0); \
\
    int position = 0; \
    while (true) { \
        int left_child = (position * 2) + 1; \
        int right_child = (position * 2) + 2; \
         \
        int greater_child = -1; \
        if (right_child < heap->size && heap->comp_func(&heap->elements[right_child], &heap->elements[left_child]) > 0) { \
            greater_child = right_child; \
        } else if (left_child < heap->size) { \
            greater_child = left_child; \
        } \
\
        if (greater_child == -1) { \
            break; \
        } \
\
        heap->elements[position] = heap->elements[greater_child]; \
        position = greater_child; \
    } \
    heap->size--; \
} \

