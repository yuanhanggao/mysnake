#include "main.h"
#include "win.h"
#include "snake.h"
#include "map.h"
#include "common.h"
#define START_X 10
#define START_Y 10

int ch;
void* key(void* arg);

int main(int args,char* argv[]){
	init_();
	srand((int)time(0));

	mvprintw_getch_snake(ALARM_POS_X, ALARM_POS_Y, "Press any button to start");
	my_win = create_newwin(HEIGHT, WIDTH, START_Y, START_X);

	bool gameover = false;
	int level;
	map* map_snake = create_map();	

	for(level = 1; level <= LEVEL_NUMS; level++){
		read_map(map_snake, level);
		mvwprintw_getch_snake(my_win, WIN_ALARM_POS_X, WIN_ALRAM_POS_Y, "LEVEL:%d", level);
		snake* game_snake = create_snake(map_snake);
		show_map(my_win, map_snake);
		show_snake(my_win, game_snake);
		generate_fruit(my_win, game_snake);
		mvprintw_snake(ALARM_POS_X, ALARM_POS_Y, "Press F4 to quit");
		mvprintw_snake(LEVEL_POS_X, LEVEL_POS_Y, "level: %d", level);
		ch = KEY_RIGHT;
		pthread_create(&thread_id, NULL, key, NULL);

		while(1){
			if (ch == KEY_F(4) ){
				gameover = true;
				break;
			}
			game_snake->ch = ch;
			move_snake(my_win, game_snake);
			if(is_crashed_snake(game_snake)){
				gameover = true;
				if( pthread_cancel(thread_id)!=0 ){
					error_handling("pthread_cancel error!");
				}
				break;
			}
			mvprintw_snake(SNAKE_LENGTH_POS_X, SNAKE_LENGTH_POS_Y,
				"length of snake: %d", length_of_snake(game_snake));
			mvprintw_snake(SNAKE_SPEED_POS_X, SNAKE_SPEED_POS_Y, 
				"speed of snake: %s", speed_of_snake(game_snake));		
			if(length_of_snake(game_snake) > PASSED_SNAKE_LENGTH){
				if( pthread_cancel(thread_id)!=0 ){
					error_handling("pthread_cancel error!");
				}
				break;
			}
			usleep(pause_time_snake(game_snake));
		}
		destroy_snake(my_win, game_snake);
		clear_map(my_win, map_snake);
		pthread_join(thread_id, NULL);
		if(gameover)
			break;	
	}

	wclear(my_win);
	destroy_map(map_snake);
	destroy_win(my_win);
	mvprintw_snake(ALARM_POS_X, ALARM_POS_Y, "exit success!");
	sleep(3);
	end_();
	return 0;
}

void* key(void* arg){
	while(1){
		int tmp_ch = getch();
		if(tmp_ch == KEY_UP || tmp_ch == KEY_DOWN ||
			tmp_ch == KEY_LEFT || tmp_ch == KEY_RIGHT ){
				ch = tmp_ch;
		} 
		if (tmp_ch == KEY_F(4)){
			ch = tmp_ch;
			break;
		}
	}
	return NULL;
}