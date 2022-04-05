#include "common.h"

pos* create_pos(int x, int y){
	pos* tmp = (pos*)malloc(sizeof(pos));
	if(tmp == NULL)
		return NULL;
	tmp->cur_x = x;
	tmp->cur_y = y;
	return tmp;	
}
