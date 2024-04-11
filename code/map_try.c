#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 16
#define LOAD_FACTOR 0.75

// Prime numbers for capacity to reduce clustering
const int primes[] = { 53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741 };

// Define structure for the map
typedef struct {
    char** keys;
    int* values;
    int size;
    int capacity_index;
} Map;

// Hash function
unsigned int hash(const char* key, int capacity) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key;
        key++;
    }
    return hash % capacity;
}

// Initialize map
Map* create_map() {
    Map* map = (Map*)malloc(sizeof(Map));
    if (map) {
        map->size = 0;
        map->capacity_index = 0;
        map->keys = (char**)calloc(primes[map->capacity_index], sizeof(char*));
        map->values = (int*)calloc(primes[map->capacity_index], sizeof(int));
    }
    return map;
}

// Resize the map when load factor exceeds a threshold
void resize(Map* map) {
    int old_capacity = primes[map->capacity_index];
    map->capacity_index++;
    int new_capacity = primes[map->capacity_index];

    char** new_keys = (char**)calloc(new_capacity, sizeof(char*));
    int* new_values = (int*)calloc(new_capacity, sizeof(int));

    // Rehash all entries
    for (int i = 0; i < old_capacity; i++) {
        if (map->keys[i]) {
            unsigned int index = hash(map->keys[i], new_capacity);
            while (new_keys[index]) {
                index = (index + 1) % new_capacity; // Linear probing
            }
            new_keys[index] = map->keys[i];
            new_values[index] = map->values[i];
        }
    }

    // Free old tables and update map properties
    free(map->keys);
    free(map->values);
    map->keys = new_keys;
    map->values = new_values;
}

// Insert a key-value pair into the map
void insert(Map* map, const char* key, int value) {
    if ((double)map->size / primes[map->capacity_index] >= LOAD_FACTOR)
        resize(map);

    int index = hash(key, primes[map->capacity_index]);
    while (map->keys[index]) {
        // Linear probing to map_find an empty slot
        if (strcmp(map->keys[index], key) == 0) {
            // Key already exists, update the value
            map->values[index] = value;
            return;
        }
        index = (index + 1) % primes[map->capacity_index];
    }

    // Insert the new key-value pair
    map->keys[index] = strdup(key);
    map->values[index] = value;
    map->size++;
}

// map_search for a value based on a key
int map_search(Map* map, const char* key) {
    int index = hash(key, primes[map->capacity_index]);
    while (map->keys[index]) {
        if (strcmp(map->keys[index], key) == 0) {
            // Key found, return the value
            return map->values[index];
        }
        index = (index + 1) % primes[map->capacity_index];
    }
    // Key not found
    return -1;
}

void rehash(Map* map, const char* key) {
    
    int old = primes[map->capacity_index];
    int new = primes[map->capacity_index];

    char** new_keys = (char**)calloc(new, sizeof(char*));
    int* new_values = (int*)calloc(new, sizeof(int));

    for (int i = 0; i < old; i++) {

        if (strcmp(map->keys[i], key) == 0) {}
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

// map_erase a key-value pair from the map
void map_erase(Map* map, const char* key) {
    int index = hash(key, primes[map->capacity_index]);
    while (map->keys[index]) {
        if (strcmp(map->keys[index], key) == 0) {
            // Key found, remove the pair
            rehash(map, key);
            map->size--;
            return;
        }
        index = (index + 1) % primes[map->capacity_index];
    }
}

// map_find if a key exists in the map
bool map_find(Map* map, const char* key) {
    int index = hash(key, primes[map->capacity_index]);
    while (map->keys[index]) {
        if (strcmp(map->keys[index], key) == 0) {
            // Key found
            return true;
        }
        index = (index + 1) % primes[map->capacity_index];
    }
    // Key not found
    return false;
}

// map_count the occurrences of a key in the map
int map_count(Map* map, const char* key) {
    int index = hash(key, primes[map->capacity_index]);
    int map_count = 0;
    while (map->keys[index]) {
        if (strcmp(map->keys[index], key) == 0) {
            // Key found
            map_count++;
        }
        index = (index + 1) % primes[map->capacity_index];
    }
    return map_count;
}

// Main function for testing
int main() {
    Map* myMap = create_map();

    // Insert key-value pairs
    insert(myMap, "apple", 10);
    insert(myMap, "banana", 20);
    insert(myMap, "orange", 30);
    insert(myMap, "apple", 40); // Overwrite value for existing key

    // map_search for values
    printf("Value for apple: %d\n", map_search(myMap, "apple"));
    printf("Value for banana: %d\n", map_search(myMap, "banana"));
    printf("Value for orange: %d\n", map_search(myMap, "orange"));

    // Check if keys exist
    printf("Does 'apple' exist? %s\n", map_find(myMap, "apple") ? "Yes" : "No");
    printf("Does 'grape' exist? %s\n", map_find(myMap, "grape") ? "Yes" : "No");

    // map_count occurrences of keys
    printf("Number of 'apple' occurrences: %d\n", map_count(myMap, "apple"));
    printf("Number of 'grape' occurrences: %d\n", map_count(myMap, "grape"));

    map_erase(myMap, "apple");
    printf("Number of 'apple' occurrences: %d\n", map_count(myMap, "apple"));


    return 0;
}