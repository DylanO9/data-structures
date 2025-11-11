/*
    Purpose: The purpose of this program is to reimplement a dynamic array to understand the inner workings of the data structure that we use on a daily basis.
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DEFAULT_CAPACITY    4

typedef struct {
    void *data; // data is a pointer to the beginning of the vector
    size_t elem_size; // elem_size tells us the size for the elements we are allocating
    size_t size; // size keeps track of the current number of elements used
    size_t capacity; // capacity keeps track of the total number of elements allowed in the Vector
} Vector;

Vector *init_vector(size_t elem_size);
void append(Vector *v, void *object);
void *get(Vector *v, unsigned int index);
void *search(Vector *v, void *object, size_t elem_size);
int pop(Vector *v);

// Driver function
int main() {
    Vector *v = init_vector(sizeof(int)); 
    int x = 5;
    append(v, &x);
    append(v, &x);
    append(v, &x);
    append(v, &x);
    append(v, &x);
    append(v, &x);
    append(v, &x);
    int y = 10;
    append(v, &y);
    int *my_x = get(v, 6);
    if (my_x == NULL) {
        printf("My access was bad!\n");
        return 0;
    }
    printf("My prev value: %d\nv[0]: %d\n", x, *my_x);
    void *temp = search(v, &y, sizeof(int));
    printf("Did I find my y element? %d\nWhat was my element? %d\n", 1 ? temp != NULL : 0, *(int *)temp);
    pop(v);
    int *t_6 = get(v, 6);
    printf("Our [6] element is: %d\n", *t_6);
    return 0;
}

Vector *init_vector(size_t elem_size) {
    Vector *new_vector = (Vector *)malloc(sizeof(Vector));
    new_vector->elem_size = elem_size;
    new_vector->size = 0;
    new_vector->capacity = DEFAULT_CAPACITY;
    new_vector->data = malloc(new_vector->elem_size * new_vector->capacity);
    return new_vector;
}

void append(Vector *v, void *object) {
    if (v->size + 1 > v->capacity) {
        size_t new_capacity = v->capacity * 2;
        void *new_data = realloc(v->data, (new_capacity * v->elem_size)); // Could use v->data, but we do not want to lose v->data if our new data allocated is NULL
        if (new_data == NULL) {
            fprintf(stderr, "Bad realloc\n");
            exit(EXIT_FAILURE);
        }
        v->data = new_data;
        v->capacity = new_capacity;
    }
    void *next_element = v->data + (v->size * v->elem_size); 
    memcpy(next_element, object, v->elem_size);
    v->size++;
}

void *get(Vector *v, unsigned int index) {
    if (index < 0 || index > v->size - 1) {
        fprintf(stderr, "Trying to access an out of range index\n");
        return NULL;
    } 
    return v->data + (v->elem_size * index);
}

void *search(Vector *v, void *object, size_t elem_size) {
    if (elem_size != v->elem_size) {
        fprintf(stderr, "Trying to search for an object that is not the same as the objects stored in the vector\n");
        return NULL;
    }
    
    for (int i = 0; i < v->size; i++) {
        // Check if this data for the next elem_size is == the object of elem_size
        void *iterator_address = v->data + (i * v->elem_size);    
        if (memcmp(iterator_address, object, elem_size) == 0)
            return iterator_address;
    }
    return NULL;
}

// We don't have to decrease the capacity of our array, so we can just clear the bits
int pop(Vector *v) {
    void *last_address = v->data + (v->elem_size * (v->size - 1));
    memset(last_address, 0, v->elem_size);
    v->size--;
}
