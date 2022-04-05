#include "map.h"
#define BUF_SIZE HEIGHT*WIDTH
#define LEVEL_POS 14

map* create_map(void){
	map* map_snake = (map*)malloc(sizeof(map));
	map_snake->map_anchor = (struct list_head*)malloc(sizeof(struct list_head));
	map_snake->map_width = WIDTH;
	map_snake->map_height = HEIGHT;
	map_snake->map_array = (int**)malloc(sizeof(int*)*map_snake->map_width);
	for(int i=0; i<map_snake->map_width; i++)
		map_snake->map_array[i] = (int*)malloc(sizeof(int)*map_snake->map_height);
	return map_snake;
}

void append_map_pos(map* map_snake, int x, int y){
	if (map_snake == NULL || 
		map_snake->map_anchor == NULL)
		return;
	pos* tmp = create_pos(x, y);
	list_add_tail(&tmp->anchor, map_snake->map_anchor);
}

void read_map(map* map_snake, int level){
	int fd_map;
	int size_map;

	char file_map[20] = "map/snake_map_";
	char level_str[2];
	bzero(level_str, 2);
	sprintf(level_str, "%d", level);
	strcat(file_map, level_str);
//	mvprintw_snake(MAP_FILE_POS_X, MAP_FILE_POS_Y, "file_map:%s", file_map);

	fd_map = open(file_map, O_RDONLY);
	if (fd_map == -1){
		error_handling("open map error!");
		return;
	}
	file_map[LEVEL_POS] = '\0';
	char map[BUF_SIZE];

	size_map = read(fd_map, map, sizeof(map));
	if( size_map == -1){
		error_handling("read map error!");
		return;
	}
	close(fd_map);	

	INIT_LIST_HEAD(map_snake->map_anchor);

	int obstacle_x = 0;
	int obstacle_y = 0;
	int m = 0;

	for(; m < size_map; m++){
		if( map[m] == '1' ){
			append_map_pos(map_snake, obstacle_x, obstacle_y);
			map_snake->map_array[obstacle_x][obstacle_y] = 1;
		}
		else if(map[m] == '\n' || obstacle_x == WIDTH){
			obstacle_x = 0;
			obstacle_y++;
		}
		obstacle_x++;
	}
	return;
}

void show_map(WINDOW* local_win, map* map_snake){
	if(map_snake->map_anchor == NULL)
		return;
	pos *tmp, *q;
	list_for_each_entry_safe(tmp, q, map_snake->map_anchor, anchor){
		mvwprintw(local_win, tmp->cur_y, tmp->cur_x, OBSTACLE_GRAPH);
	}
    wrefresh(local_win);
	return;
}

void clear_map(WINDOW* local_win, map* map_snake){
	if( map_snake == NULL ||
		map_snake->map_anchor == NULL)
		return;	
	pos *tmp, *q;
	list_for_each_entry_safe(tmp, q, map_snake->map_anchor, anchor){
		list_del(&tmp->anchor);
		map_snake->map_array[tmp->cur_x][tmp->cur_y] = 0;
		mvwprintw(local_win, tmp->cur_y, tmp->cur_x, NULL_GRAPH);
    	wrefresh(local_win);
		usleep(20000);
		free(tmp);
	}	
	return;
}

void destroy_map(map* map_snake){
	if(map_snake == NULL)
		return;
	free(map_snake->map_anchor);
	for(int i=0; i<map_snake->map_width; i++)
		free(map_snake->map_array[i]);
	free(map_snake->map_array);
}