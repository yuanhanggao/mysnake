#ifndef _MAP_H
#define _MAP_H

#include "main.h"
#include "common.h"
typedef struct map_attr{
    struct list_head* map_anchor;
    int** map_array;
    int map_width;
    int map_height;
}map;

#define LEVEL_NUMS 2

map* create_map(void);
void append_map_pos(map* map_snake, int x, int y);
void read_map(map* map_snake, int level);
void show_map(WINDOW* local_win, map* map_snake);
void clear_map(WINDOW* local_win, map* map_snake);
void destroy_map(map* map_snake);


#endif