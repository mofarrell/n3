/*The MIT License (MIT)
 *
 *Copyright (c) 2014 Michael O'Farrell, Bram Wasti
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy
 *of this software and associated documentation files (the "Software"), to deal
 *in the Software without restriction, including without limitation the rights
 *to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *copies of the Software, and to permit persons to whom the Software is
 *furnished to do so, subject to the following conditions:
 *
 *The above copyright notice and this permission notice shall be included in
 *all copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *THE SOFTWARE.
 *
 */

/*
 * This file will be used to draw to the screen using ncurses
 */

#include "display.h"

WINDOW *main_screen;

/* private functions */
void n3_init_colors(void);

void n3_init_screen(void){
    main_screen = initscr();
    keypad(stdscr, TRUE);           // keypad enabled
    (void) nodelay(main_screen, 1); // no blocking
    (void) nonl();                  // no new lines
    (void) noecho();                // don't print to screen
    n3_init_colors();
    refresh();
}

/*
 * crazy shifting is to set up every color 
*/
void n3_init_colors(void){
  start_color();
   for (int i = 0; i < (1 << 8); i ++) {
      int r = i >> 5;
      int g = (i >> 2) & 0b111;
      int b = i & 0b111;
      init_color(i, r, g, b);
      init_pair(i, i, 0); // 0 --> i if you want pure blocks, otherwise ascii
  }
  return;
}

void n3_end_screen(void){
    endwin();
}

/* allow us to directly map to the 216 colors ncurses makes available */
static inline int get_color(int r, int g, int b){
  return 16+r/48*36+g/48*6+b/48; 
}

const char *sizes = "=+*%%@#";

/* vector drawer
 */
int n3_vector_draw(std::vector<std::uint8_t> data, int width, int height){
    for (int y=0; y<height; y++){
        for (int x=0; x<width; x++){
            int intensity = (data[((height-y-1)*width+x)*4] +
            data[((height-y-1)*width+x)*4+1] + 
            data[((height-y-1)*width+x)*4+2])/127;
            int color = get_color(
                    data[((height-y-1)*width+x)*4],
                    data[((height-y-1)*width+x)*4+1],
                    data[((height-y-1)*width+x)*4+2]);
            mvaddch(y, x, sizes[intensity]|COLOR_PAIR(color));
        }
    }
    return 0;
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

