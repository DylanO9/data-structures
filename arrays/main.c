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
    int *my_x = get(v, 6);
    if (my_x == NULL) {
        printf("My access was bad!\n");
        return 0;
    }
    printf("My prev value: %d\nv[0]: %d\n", x, *my_x);
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
        void *new_data = realloc(v->data, (new_capacity * v->elem_size));
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
