#ifndef _SNAKE_H
#define _SNAKE_H

#include "main.h"
#include "map.h"
#include "common.h"

#define SLOW_SPEED 500000
#define MEDIUM_SPEED 350000
#define FAST_SPEED 200000
#define VERYFAST_SPEED 100000

#define SLOW_SPEED_TEXT "slow" 
#define MEDIUM_SPEED_TEXT "medium" 
#define FAST_SPEED_TEXT "fast"
#define VERYFAST_SPEED_TEXT "vert fast"

#define MEDIUM_SPEED_LENGTH 9  
#define FAST_SPEED_LENGTH 15
#define VERYFAST_SPEED_LENGTH 22
#define PASSED_SNAKE_LENGTH 25

typedef struct fruit_attr{
	pos fruit_pos;
}fruit;

typedef struct snake_attr{
	struct list_head* snake_anchor;
	int ch;
	int direction_snake;
	map* map_snake;
	fruit* wanted_fruit;
}snake;


snake* create_snake(map* map_snake);
void append_snake_head(snake* this_snake, int x, int y);
void del_snake_tail(snake* this_snake);
void destroy_snake(WINDOW* local_win, snake* this_snake);
int length_of_snake(snake* this_snake);
int pause_time_snake(snake* this_snake);
char* speed_of_snake(snake* this_snake);
void show_snake(WINDOW* local_win, snake* this_snake);
void move_snake(WINDOW* local_win, snake* this_snake);
bool is_crashed_fruit(int fruit_x, int fruit_y, snake* this_snake);
bool is_crashed_snake(snake* this_snake);
void generate_fruit(WINDOW* local_win, snake* this_snake);

#endif