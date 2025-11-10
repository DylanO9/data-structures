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

// Driver function
int main() {
    Vector *new_vector = init_vector(sizeof(int)); 
    int x = 5;
    append(new_vector, &x);
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
        size_t new_size = v->capacity * 2;
        v->data = realloc(v->data, new_size);
        if (v->data == NULL) {
            fprintf(stderr, "Bad realloc\n");
            exit(EXIT_FAILURE);
        }
    }
    void *next_element = v->data + (v->size * v->elem_size); 
    memcpy(next_element, object, v->elem_size);
    v->size++;
}


