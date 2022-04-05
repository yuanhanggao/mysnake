#include "win.h"

void init_(){
	initscr();
	raw();
	noecho();
	keypad(stdscr,TRUE);
	curs_set(0);
}

void end_(){
	endwin();
}

WINDOW* create_newwin(int height, int width, int starty, int startx){
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0); /* 0, 0是字符默认的行列起始位置*/
    wrefresh(local_win); /*刷新窗口缓冲，显示box */
    return local_win;
}

void destroy_win(WINDOW* local_win){
    wborder(local_win,' ',' ',' ',' ',' ',' ',' ',' ');
    /*参数注解9.3：
    * 1. win:当前操作的窗口
    * 2. ls:用于显示窗口左边界的字符
    * 3. rs:用于显示窗口右边界的字符
    * 4. ts:用于显示窗口上边界的字符
    * 5. bs:用于显示窗口下边界的字符
    * 6. tl:用于显示窗口左上角的字符
    * 7. tr:用于显示窗口右上角的字符
    * 8. bl:用于显示窗口左下角的字符
    * 9. br:用于显示窗口右下角的字符
    */
    wrefresh(local_win);
    delwin(local_win);
}
