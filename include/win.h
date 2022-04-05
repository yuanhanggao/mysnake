#ifndef _WIN_H
#define _WIN_H
#include "main.h"


void init_();   // init the main_window
void end_();    // destroy the main_window
WINDOW* create_newwin(int height, int width, int starty, int startx);// create a new window
void destroy_win(WINDOW* local_win); //destroy the specific window

#endif