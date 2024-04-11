# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "Vector.h"

#define INITIAL_CAPACITY 10

void Init_vector(Vector* vec) {
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
    
}

void Vector_push_back(Vector* vec, const char* str) {
    if (vec->size >= vec->capacity) {
        vec->capacity = (vec->capacity == 0) ? 1 : vec->capacity * 2;
        vec->data = realloc(vec->data, vec->capacity * sizeof(char*));
        if (vec->data == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }

    vec->data[vec->size] = strdup(str); 
    if (vec->data[vec->size] == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    vec->size++;
}

int Vector_search(Vector* vec, const char* str) {
    for (size_t i = 0; i < vec->size; i++) {
        if (strcmp(vec->data[i], str) == 0) {
            return 1; // Found
        }
    }
    return 0; // Not found
}

int Vector_size(Vector* vec) {
    return vec->size;
}

const char* Vector_at(Vector* vec, int index) {
    if (index >= vec->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return vec->data[index];
}

int Vector_isempty(Vector* vec) {
    return vec->size == 0;
}

void Vector_pop_back(Vector* vec) {
    if (vec->size > 0) {
        free(vec->data[vec->size - 1]);
        vec->size--;
    }
}


void Vector_free(Vector* vec) {
    for (size_t i = 0; i < vec->size; i++) {
        free(vec->data[i]);
    }
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}

// int main() {
//     Vector vec;
//     Init_vector(&vec);

//     Vector_push_back(&vec, "Hello");
//     Vector_push_back(&vec, "World");
//     Vector_push_back(&vec, "!");

//     for (size_t i = 0; i < vec.size; i++) {
//         printf("%s ", Vector_at(&vec, i));
//     }
//     printf("\n");

//     Vector_pop_back(&vec);

//     for (size_t i = 0; i < vec.size; i++) {
//         printf("%s ", Vector_at(&vec, i));
//     }
//     printf("\n");

//     // Check if the vector is empty
//     if (Vector_isempty(&vec)) {
//         printf("Vector is empty\n");
//     } else {
//         printf("Vector is not empty\n");
//     }

//     // Free the memory
//     Vector_free(&vec);

//     return 0;
// }
