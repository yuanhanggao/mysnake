#ifndef _COMMON_H
#define _COMMON_H

#include "list.h"
#include <ncurses.h>
#include <stdlib.h>

#define SNAKE_HEAD_GRAPH "0"
#define SNAKE_BODY_GRAPH "*"
#define FRUIT_GRAPH "f"
#define NULL_GRAPH " "
#define OBSTACLE_GRAPH "1"

#define ALARM_POS_X 0
#define ALARM_POS_Y 0
#define LEVEL_POS_X 0
#define LEVEL_POS_Y 1
#define SNAKE_LENGTH_POS_X 0
#define SNAKE_LENGTH_POS_Y 2
#define SNAKE_SPEED_POS_X 0
#define SNAKE_SPEED_POS_Y 3
#define MAP_FILE_POS_X 0
#define MAP_FILE_POS_Y 4 
#define ERROR_MESSAGE_POS_X 0
#define ERRPR_MESSAGE_POS_Y 5 

#define MAX_MESSAGE_LEGNTH 25
#define NULL_MESSAGE_BEFORE_PRINT "                         "

#define WIN_ALARM_POS_X 5
#define WIN_ALRAM_POS_Y 5

#define mvprintw_snake(x, y, args...) \
		do{\
			mvprintw(y, x, NULL_MESSAGE_BEFORE_PRINT); \
    		mvprintw(y, x, ##args); \
    		refresh(); \
		}while(0)

#define mvwprintw_snake(local_win, x, y, args...) \
		do{\
			mvwprintw(local_win, y, x, NULL_MESSAGE_BEFORE_PRINT); \
			mvwprintw(local_win, y, x, ##args); \
			wrefresh(local_win); \
		}while(0)

#define error_handling(args...) \
		do{\
		   	mvprintw(ERRPR_MESSAGE_POS_Y, ERROR_MESSAGE_POS_X, NULL_MESSAGE_BEFORE_PRINT);\
			mvprintw(ERRPR_MESSAGE_POS_Y, ERROR_MESSAGE_POS_X, ##args);\
			refresh(); \
		}while(0)

#define mvprintw_getch_snake(x, y, args...) \
		do{ \
		    mvprintw_snake(x, y, ##args); \
		    getch(); \
		    mvprintw(y, x, NULL_MESSAGE_BEFORE_PRINT); \
		    refresh(); \
		}while(0)

#define mvwprintw_getch_snake(local_win, x, y, args...) \
		do{ \
		    mvwprintw_snake(local_win, x, y, ##args); \
		    getch(); \
		    mvwprintw(local_win, y, x, NULL_MESSAGE_BEFORE_PRINT); \
		    wrefresh(local_win); \
		}while(0)

typedef struct list_pos{
	int cur_y,cur_x;
	struct list_head anchor;                    
}pos;

pos* create_pos(int x, int y);
#endif 