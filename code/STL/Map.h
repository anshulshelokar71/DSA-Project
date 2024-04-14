# include <stdbool.h>

typedef struct {
    char **keys;
    int *values;
    int size;
    int capacity_index;
} Map;


unsigned int hash(const char *key, int cp);
void Init_map(Map **m);
void resize(Map *map);
void map_insert(Map *map, const char *key, int value);
int map_get(Map *map, const char *key);
void rehash(Map *map, const char *key);
void map_erase(Map *map, const char *key);
bool map_find(Map *map, const char *key);
