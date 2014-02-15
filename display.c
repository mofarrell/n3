/*
 * This file will be used to draw to the screen using ncurses
 */

#include <ncurses.h>
#include "display.h"

void init_screen(){
    initscr();
    start_color();

}
