#include "snake.h"


snake* create_snake(map* map_snake){
	snake* this_snake = (snake*)malloc(sizeof(snake));
	this_snake->snake_anchor = (struct list_head*)malloc(sizeof(struct list_head));
	INIT_LIST_HEAD(this_snake->snake_anchor);
	pos* tmp = create_pos(5 , 10);
	list_add_tail(&tmp->anchor, this_snake->snake_anchor);
    append_snake_head(this_snake, 6, 10);
    append_snake_head(this_snake, 7, 10);
    append_snake_head(this_snake, 8, 10);
    append_snake_head(this_snake, 9, 10);
    append_snake_head(this_snake, 10, 10);
	this_snake->ch = KEY_RIGHT;
	this_snake->direction_snake = KEY_RIGHT;
	this_snake->map_snake = map_snake;
	this_snake->wanted_fruit = (fruit*)malloc(sizeof(fruit));
	return this_snake;
} 

void append_snake_head(snake* this_snake, int x, int y){
	if (this_snake == NULL ||
		this_snake->snake_anchor == NULL) 
		return;
	pos* tmp = create_pos(x, y);
	list_add_tail(&tmp->anchor, this_snake->snake_anchor);
}

void del_snake_tail(snake* this_snake){
	if(this_snake == NULL || 
		this_snake->snake_anchor == NULL)
		return;
	pos* snake_tail = list_entry(this_snake->snake_anchor->next, pos, anchor);	
	list_del(&snake_tail->anchor);
	free(snake_tail);
}

void destroy_snake(WINDOW* local_win, snake* this_snake){
	if(this_snake == NULL)
		return;	
	pos *tmp, *q;
	list_for_each_entry_safe(tmp, q, this_snake->snake_anchor, anchor){
		list_del(&tmp->anchor);
		mvwprintw(local_win, tmp->cur_y, tmp->cur_x, NULL_GRAPH);
    	wrefresh(local_win);
		usleep(200000);
		free(tmp);
	}
	free(this_snake->snake_anchor);
	this_snake->map_snake == NULL;
	free(this_snake->wanted_fruit);
	free(this_snake);	
	return;
}

int length_of_snake(snake* this_snake){
	int result=0;
	if(this_snake == NULL ||
		this_snake->snake_anchor == NULL)
		return 0;	
	pos *tmp, *q;
	list_for_each_entry_safe(tmp, q, this_snake->snake_anchor, anchor){
		result++;
	}	
	return result;
}

int pause_time_snake(snake* this_snake){
	int length_snake = length_of_snake(this_snake);
	if(length_snake <= MEDIUM_SPEED_LENGTH)
		return SLOW_SPEED;
	else if(length_snake <= FAST_SPEED_LENGTH)
		return MEDIUM_SPEED;
	else if(length_snake <= VERYFAST_SPEED_LENGTH)
		return FAST_SPEED;
	else 
		return VERYFAST_SPEED;
}

char* speed_of_snake(snake* this_snake){
	int length_snake = length_of_snake(this_snake);
	if(length_snake <= MEDIUM_SPEED_LENGTH)
		return SLOW_SPEED_TEXT;
	else if(length_snake <= FAST_SPEED_LENGTH)
		return MEDIUM_SPEED_TEXT;
	else if(length_snake <= VERYFAST_SPEED_LENGTH)
		return FAST_SPEED_TEXT;
	else
		return VERYFAST_SPEED_TEXT;
	
}

void show_snake(WINDOW* local_win, snake* this_snake){
	if(this_snake == NULL ||
		this_snake->snake_anchor == NULL)
		return;
	pos *snake_head;  	
	snake_head = list_entry(this_snake->snake_anchor->prev, pos, anchor);
	pos *tmp, *q;
	list_for_each_entry_safe(tmp, q, this_snake->snake_anchor, anchor){
		if (tmp == snake_head)
			mvwprintw(local_win, tmp->cur_y, tmp->cur_x, SNAKE_HEAD_GRAPH);
		else
			mvwprintw(local_win, tmp->cur_y, tmp->cur_x, SNAKE_BODY_GRAPH);
	}
    wrefresh(local_win);
	return;
}

void move_snake(WINDOW* local_win, snake* this_snake){
	if(local_win == NULL || this_snake == NULL)
		return;
	int new_head_x, new_head_y;
	pos* snake_head;
	pos* snake_tail;

	snake_head = list_entry(this_snake->snake_anchor->prev, pos, anchor);
	snake_tail = list_entry(this_snake->snake_anchor->next, pos, anchor);
	new_head_x = snake_head->cur_x;
	new_head_y = snake_head->cur_y;

	switch(this_snake->ch){
		case KEY_LEFT:
			if(this_snake->direction_snake != KEY_RIGHT)
				this_snake->direction_snake = this_snake->ch;
			break;
		case KEY_RIGHT:
			if(this_snake->direction_snake != KEY_LEFT)
				this_snake->direction_snake = this_snake->ch;
			break;
		case KEY_UP:
			if(this_snake->direction_snake != KEY_DOWN)
				this_snake->direction_snake = this_snake->ch;
			break;
		case KEY_DOWN:
			if(this_snake->direction_snake != KEY_UP)
				this_snake->direction_snake = this_snake->ch;
			break;
	}
	switch(this_snake->direction_snake){
		case KEY_LEFT:
			new_head_x--;
			break;
		case KEY_RIGHT:
			new_head_x++;
			break;
		case KEY_UP:
			new_head_y--;
			break;
		case KEY_DOWN:
			new_head_y++;
			break;
	}

	mvwprintw(local_win, new_head_y, new_head_x, SNAKE_HEAD_GRAPH);
	mvwprintw(local_win, snake_head->cur_y, snake_head->cur_x, SNAKE_BODY_GRAPH);
    append_snake_head(this_snake, new_head_x, new_head_y);

	if (new_head_x == this_snake->wanted_fruit->fruit_pos.cur_x && 
		new_head_y == this_snake->wanted_fruit->fruit_pos.cur_y){
		if(length_of_snake(this_snake) <= PASSED_SNAKE_LENGTH)
			generate_fruit(local_win, this_snake);
		}
	else{
		mvwprintw(local_win, snake_tail->cur_y, snake_tail->cur_x, NULL_GRAPH);
		del_snake_tail(this_snake);
	}
	wrefresh(local_win);
	return;
}

bool is_crashed_fruit(int fruit_x, int fruit_y, snake* this_snake){
	if (this_snake == NULL ||
		this_snake->snake_anchor == NULL ||
		this_snake->wanted_fruit == NULL)
		return true;

	pos *tmp, *q;
	list_for_each_entry_safe(tmp, q, this_snake->snake_anchor, anchor){
		if (tmp->cur_x == fruit_x &&
			tmp->cur_y == fruit_y)
			return true;
	}

	if(this_snake->map_snake->map_array[fruit_x][fruit_y] == 1)
		return true;
	return false;
}

bool is_crashed_snake(snake* this_snake){
	if (this_snake == NULL ||
		this_snake->snake_anchor == NULL)
		return true;
	pos *snake_head;
	snake_head = list_entry(this_snake->snake_anchor->prev, pos, anchor);
	if (snake_head->cur_x <= 0 || snake_head->cur_x >= WIDTH 
		|| snake_head->cur_y <= 0 || snake_head->cur_y >= HEIGHT ){
		return true;                           //  touch the boundary?      
	}

	pos *tmp, *q;
	list_for_each_entry_safe(tmp, q, this_snake->snake_anchor, anchor){
		if (tmp != snake_head){
			if (tmp->cur_x == snake_head->cur_x &&
				tmp->cur_y == snake_head->cur_y)
				return true;
		}
	}

	if(this_snake->map_snake->map_array[snake_head->cur_x][snake_head->cur_y] == 1)
		return true;
	return false;
}

void generate_fruit(WINDOW* local_win, snake* this_snake){
	int fruit_x, fruit_y;
	do{
		fruit_y = rand() % (HEIGHT -2) + 1;
		fruit_x = rand() % (WIDTH -2) + 1;
	}while(is_crashed_fruit(fruit_x, fruit_y, this_snake));

	mvwprintw(local_win, fruit_y, fruit_x, FRUIT_GRAPH);
	wrefresh(local_win);

	this_snake->wanted_fruit->fruit_pos.cur_x = fruit_x;
	this_snake->wanted_fruit->fruit_pos.cur_y = fruit_y;
}
