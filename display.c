/*
 * This file will be used to draw to the screen using ncurses
 */

#include <ncurses.h>
#include "display.h"

void init_screen(){
    initscr();
    start_color();
}


/* 
 * draws char to (x,y)
 * returns -1 on error
 */
int draw_xy(char c, int x, int y){
    if (x > COLS || x < 0 || y > LINES || y < 0) {
        return -1;
    } else {
        mvaddch(x, y, c);   
        return 0;
    }
}

/* call every screen refresh
 */
void refresh(){
    refresh();
}
