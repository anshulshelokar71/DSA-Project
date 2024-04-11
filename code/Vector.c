# include <stdio.h>
# include <stdlib.h>
# include "Vector.h"

void Init_vector(Vector* vec) {
    vec->array = NULL;
    vec->size = 0;
    vec->capacity = 0;
}


void Vector_push_back(Vector* vec, int value) {

    if (vec->size >= vec->capacity) {
        vec->capacity = (vec->capacity == 0) ? 1 : vec->capacity * 2; 
        vec->array = realloc(vec->array, vec->capacity * sizeof(int)); 
    }
    

    vec->array[vec->size] = value;
    vec->size++;
}


void Vector_pop_back(Vector* vec) {
    if (vec->size > 0) {
        vec->size--;
    }
}


int Vector_at(Vector* vec, size_t index) {
    if (index >= vec->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return vec->array[index];
}


int Vector_isempty(Vector* vec) {
    return vec->size == 0;
}


void Vector_free(Vector* vec) {
    free(vec->array);
    vec->array = NULL;
    vec->size = 0;
    vec->capacity = 0;
}

// int main() {
//     Vector my_vector;
//     Init_vector(&my_vector);

//     // Push some elements to the vector
//     Vector_push_back(&my_vector, 10);
//     Vector_push_back(&my_vector, 20);
//     Vector_push_back(&my_vector, 30);

//     // Access and print elements
//     for (size_t i = 0; i < my_vector.size; i++) {
//         printf("%d ", Vector_at(&my_vector, i));
//     }
//     printf("\n");

//     // Pop an element from the vector
//     Vector_pop_back(&my_vector);

//     // Print the vector after popping
//     for (size_t i = 0; i < my_vector.size; i++) {
//         printf("%d ", Vector_at(&my_vector, i));
//     }
//     printf("\n");

//     // Check if the vector is empty
//     if (Vector_isempty(&my_vector)) {
//         printf("Vector is empty\n");
//     } else {
//         printf("Vector is not empty\n");
//     }

//     // Free the memory
//     Vector_free(&my_vector);

//     return 0;
// }
