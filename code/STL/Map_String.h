#ifndef MAP_STRING
#define MAP_STRING

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 16
#define LOAD_FACTOR 0.75


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

#endif