# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include "Map.h"

#define INITIAL_CAPACITY 16
#define LOAD_FACTOR 0.50
const int primes[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};


unsigned int hash(const char *key, int cp) {

    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key;
        key++;
    }

    return hash % cp;
}


void Init_map(Map **m) {

    Map *map = (Map *)malloc(sizeof(Map));
    if (map) {
        map->size = 0;
        map->capacity_index = 0;
        map->keys = (char **)calloc(primes[map->capacity_index], sizeof(char *));
        map->values = (int *)calloc(primes[map->capacity_index], sizeof(int));
    }

    *m = map;
}


void resize(Map *map) {

    int old_capacity = primes[map->capacity_index++];
    int new_capacity = primes[map->capacity_index];

    char **new_keys = (char **)calloc(new_capacity, sizeof(char *));
    int *new_values = (int *)calloc(new_capacity, sizeof(int));

    for (int i = 0; i < old_capacity; i++) {

        if (map->keys[i]) {

            unsigned int index = hash(map->keys[i], new_capacity);
            while (new_keys[index])
                index = (index + 1) % new_capacity;

            new_keys[index] = map->keys[i];
            new_values[index] = map->values[i];
        }
    }

    free(map->keys);
    free(map->values);
    map->keys = new_keys;
    map->values = new_values;
}


void map_insert(Map *map, const char *key, int value) {

    if ((double)map->size / primes[map->capacity_index] >= LOAD_FACTOR)
        resize(map);

    int index = hash(key, primes[map->capacity_index]);
    while (map->keys[index]) {

        if (strcmp(map->keys[index], key) == 0) {
            map->values[index] = value;
            return;
        }
        index = (index + 1) % primes[map->capacity_index];
    }

    map->keys[index] = strdup(key);
    map->values[index] = value;
    map->size++;
}


int map_get(Map *map, const char *key) {

    int index = hash(key, primes[map->capacity_index]);
    while (map->keys[index]) {

        if (strcmp(map->keys[index], key) == 0) {
            return map->values[index];
        }
        index = (index + 1) % primes[map->capacity_index];
    }

    return -1;
}


void rehash(Map *map, const char *key) {

    int old = primes[map->capacity_index];
    int new = primes[map->capacity_index];

    char **new_keys = (char **)calloc(new, sizeof(char *));
    int *new_values = (int *)calloc(new, sizeof(int));

    for (int i = 0; i < old; i++) {

        if (map->keys[i] && strcmp(map->keys[i], key) == 0) {}
        else if (map->keys[i]) {

            unsigned int index = hash(map->keys[i], new);
            while (new_keys[index])
                index = (index + 1) % new;

            new_keys[index] = map->keys[i];
            new_values[index] = map->values[i];
        }
    }

    free(map->keys);
    free(map->values);
    map->keys = new_keys;
    map->values = new_values;
}


void map_erase(Map *map, const char *key) {

    int index = hash(key, primes[map->capacity_index]);
    while (map->keys[index]) {

        if (strcmp(map->keys[index], key) == 0) {
            rehash(map, key);
            map->size--;
            return;
        }
        index = (index + 1) % primes[map->capacity_index];
    }
}


bool map_find(Map *map, const char *key) {

    int index = hash(key, primes[map->capacity_index]);
    while (map->keys[index]) {

        if (strcmp(map->keys[index], key) == 0) {
            return true;
        }
        index = (index + 1) % primes[map->capacity_index];
    }

    return false;
}


// int main() {

//     Map *myMap;
//     Init_map(&myMap);

//     map_insert(myMap, "apple", 10);
//     map_insert(myMap, "apple", 40); // Overwrite value for existing key

//     printf("Value for apple: %d\n", map_get(myMap, "apple"));

//     // Check if keys exist
//     printf("Does 'apple' exist? %s\n", map_find(myMap, "apple") ? "Yes" : "No");

//     map_erase(myMap, "apple");
//     printf("Does 'apple' exist? %s\n", map_find(myMap, "apple") ? "Yes" : "No");

//     return 0;
// }