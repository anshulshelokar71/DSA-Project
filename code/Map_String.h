#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 16
#define LOAD_FACTOR 0.75
const int primes[] = {
    53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613,
    393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653,
    100663319, 201326611, 402653189, 805306457, 1610612741
};

typedef struct {
    char **keys;
    char **values;
    int size;
    int capacity_index;
} Map;

unsigned int hash(const char *key, int cp);
void Init_map(Map **m);
void resize(Map *map);
void map_insert(Map *map, const char *key, const char *value);
const char *map_get(Map *map, const char *key);
void map_erase(Map *map, const char *key) ;
bool map_find(Map *map, const char *key);