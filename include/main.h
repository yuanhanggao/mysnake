#ifndef _MAIN_H
#define _MAIN_H

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <utime.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ncurses.h>
#include "list.h"

#define WIDTH 45
#define HEIGHT 20

WINDOW *my_win;
pthread_mutex_t mutex;
pthread_t thread_id;

#endif