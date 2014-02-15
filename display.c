/*
 * This file will be used to draw to the screen using ncurses
 */

#include <ncurses.h>
#include "display.h"

WINDOW *main_screen;

/* private functions */
void n3_init_colors(void);

void n3_init_screen(void){
    main_screen = initscr();
    keypad(stdscr, TRUE);           // keypad enabled
    (void) nodelay(main_screen, 1); // no blocking
    (void) nonl();                  // no new lines
    (void) cbreak();                // use sighandlers for keyboard kills
    (void) noecho();                // don't print to screen
    n3_init_colors();
    mvaddch(0,0,'A');
    refresh();
}

void n3_init_colors(void){
    start_color();
    init_pair(1, COLOR_RED,     COLOR_BLACK);
    init_pair(2, COLOR_GREEN,   COLOR_BLACK);
    init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
    init_pair(4, COLOR_BLUE,    COLOR_BLACK);
    init_pair(5, COLOR_CYAN,    COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_WHITE,   COLOR_BLACK);
}

void n3_end_screen(void){
    endwin();
}

/* 
 * draws char to (x,y)
 * returns -1 on error
 */
int n3_draw_xy(char c, int x, int y){
    if (x > COLS || x < 0 || y > LINES || y < 0) {
        return -1;
    } else {
        mvaddch(x, y, c);   
        return 0;
    }
}

/* call every screen refresh
 */
void n3_refresh(){
    refresh();
}
