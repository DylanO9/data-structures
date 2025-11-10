/*
    Purpose: The purpose of this program is to reimplement a dynamic array to understand the inner workings of the data structure that we use on a daily basis.
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    void *data; // data is a pointer to the beginning of the vector
    size_t elem_size; // elem_size tells us the size for the elements we are allocating
    size_t size; // size keeps track of the current number of elements used
    size_t capacity; // capacity keeps track of the total number of elements allowed in the Vector
} Vector;

Vector *init_vector(size_t elem_size);

// Driver function
int main() {
    Vector *new_vector = init_vector(sizeof(int)); 
    return 0;
}

Vector *init_vector(size_t elem_size) {
    Vector *new_vector = (Vector *)malloc(sizeof(Vector));
    new_vector->elem_size = elem_size;
    new_vector->size = 0;
    new_vector->capacity = 0;
    return new_vector;
}



