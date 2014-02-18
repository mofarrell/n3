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
//    (void) cbreak();                // use sighandlers for keyboard kills
    (void) noecho();                // don't print to screen
    n3_init_colors();
    refresh();
}

#define BITS_PER_COLOR 2
#define BITS_PER_COLOR_BLUE 2
#define COLOR_SIZE (1 << BITS_PER_COLOR)
#define COLOR_SIZE_BLUE (1 << BITS_PER_COLOR_BLUE)
static inline int color_index(int r, int g, int b) {
  //printf("%d\n", r*COLOR_SIZE*COLOR_SIZE_BLUE + g*COLOR_SIZE_BLUE + b + 1);
  //if (r*COLOR_SIZE*COLOR_SIZE_BLUE + g*COLOR_SIZE_BLUE + b + 1 > 64)
    //exit(1);
  return r*COLOR_SIZE*COLOR_SIZE + g*COLOR_SIZE + b + 1;
}

static inline int color_index2(int r, int g, int b) {
  //printf("%d\n", r*COLOR_SIZE*COLOR_SIZE_BLUE + g*COLOR_SIZE_BLUE + b + 1);
  //if (r*COLOR_SIZE*COLOR_SIZE_BLUE + g*COLOR_SIZE_BLUE + b + 1 > 64)
    //exit(1);
  return r + g + b > 1 ? r+b+g/3 : 0;
  return r*COLOR_SIZE*COLOR_SIZE + g*COLOR_SIZE + b + 1;
}

void n3_init_colors(void){
  start_color();
   for (int i = 0; i < (1 << 8); i ++) {
      int r = i >> 5;
      int g = (i >> 2) & 0b111;
      int b = i & 0b111;
      init_color(i, r, g, b);
      init_pair(i, i, 0); // 0 --> i if you want pure blocks, else # ascii
  }
  return;
 
/*  for (int r = 0; r < COLOR_SIZE; r++) {
    for (int g = 0; g < COLOR_SIZE; g++) {
      for (int b = 0; b < COLOR_SIZE_BLUE; b++) {
        if (init_color(color_index(r,g,b), r*1000/(COLOR_SIZE - 1), g*1000/(COLOR_SIZE - 1), b*1000/(COLOR_SIZE_BLUE - 1)) == ERR){
          std::cout << "SHIT!\n" << std::endl;exit(1);}
        if (init_pair(color_index(r,g,b), color_index(r,g,b), 0) == ERR){
          std::cout << "FUC ME " << std::endl;exit(1);
        }  
      }
    }
  }*/
}

void n3_end_screen(void){
    endwin();
}

static inline int get_color(int r, int g, int b){
  return 16+r/48*36+g/48*6+b/48;
  /*return color_index2(r >> (8-BITS_PER_COLOR), 
                     g >> (8-BITS_PER_COLOR), 
                     b >> (8-BITS_PER_COLOR)
                    );*/
}

/* vector drawer
 */
int n3_vector_draw(std::vector<std::uint8_t> data, int width, int height){
    for (int y=0; y<height; y++){
        for (int x=0; x<width; x++){
            int color = get_color(
                    data[((height-y-1)*width+x)*4],
                    data[((height-y-1)*width+x)*4+1],
                    data[((height-y-1)*width+x)*4+2]);
            //attron(COLOR_PAIR(color));
            //printf("%d", color);
            mvaddch(y, x, '#'|COLOR_PAIR(color));
        }
       // mvaddnstr(y, 0, (char *)data.data(), width);
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

/*
int n3_string_xy(char *str, int length, int x, int y){
    mvaddchnstr(y, x, str, length);
    return 0;
}
*/
/* call every screen refresh
 */
void n3_refresh(){
    refresh();
}
