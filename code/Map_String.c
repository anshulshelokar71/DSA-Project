#include"Map_String.h"


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
        map->values = (char **)calloc(primes[map->capacity_index], sizeof(char *));
    }
    *m = map;
}

void resize(Map *map) {
    int old_capacity = primes[map->capacity_index++];
    int new_capacity = primes[map->capacity_index];
    char **new_keys = (char **)calloc(new_capacity, sizeof(char *));
    char **new_values = (char **)calloc(new_capacity, sizeof(char *));
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

void map_insert(Map *map, const char *key, const char *value) {
    if ((double)map->size / primes[map->capacity_index] >= LOAD_FACTOR)
        resize(map);
    int index = hash(key, primes[map->capacity_index]);
    while (map->keys[index]) {
        if (strcmp(map->keys[index], key) == 0) {
            free(map->values[index]);
            map->values[index] = strdup(value);
            return;
        }
        index = (index + 1) % primes[map->capacity_index];
    }
    map->keys[index] = strdup(key);
    map->values[index] = strdup(value);
    map->size++;
}

const char *map_get(Map *map, const char *key) {
    int index = hash(key, primes[map->capacity_index]);
    while (map->keys[index]) {
        if (strcmp(map->keys[index], key) == 0) {
            return map->values[index];
        }
        index = (index + 1) % primes[map->capacity_index];
    }
    return NULL;
}

void map_erase(Map *map, const char *key) {
    int index = hash(key, primes[map->capacity_index]);
    while (map->keys[index]) {
        if (strcmp(map->keys[index], key) == 0) {
            free(map->keys[index]);
            free(map->values[index]);
            map->keys[index] = NULL;
            map->values[index] = NULL;
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

//     map_insert(myMap, "apple", "10");
//     map_insert(myMap, "banana", "20");
//     map_insert(myMap, "orange", "30");
//     map_insert(myMap, "apple", "40"); // Overwrite value for existing key

//     printf("Value for apple: %s\n", map_get(myMap, "apple"));
//     printf("Value for banana: %s\n", map_get(myMap, "banana"));
//     printf("Value for orange: %s\n", map_get(myMap, "orange"));

//     // Check if keys exist
//     printf("Does 'apple' exist? %s\n", map_find(myMap, "apple") ? "Yes" : "No");
//     printf("Does 'grape' exist? %s\n", map_find(myMap, "grape") ? "Yes" : "No");

//     map_erase(myMap, "apple");
//     printf("Does 'apple' exist? %s\n", map_find(myMap, "apple") ? "Yes" : "No");

//     return 0;
// }
