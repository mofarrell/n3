/*
 * This file will be used to draw to the screen using ncurses
 */

#include "display.h"

WINDOW *main_screen;
char sizes[] = ".:-=+*%%@#";

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
    refresh();
}

void n3_init_colors(void){
    start_color();
    init_color(0, 1000, 1000, 1000);
    init_color(1, 1000, 500, 500);
    init_color(2, 500, 1000, 500);
    init_color(3, 500, 500, 1000);
    init_color(4, 500, 1000, 1000);
    init_color(5, 1000, 500, 1000);
    init_color(6, 1000, 1000, 500);
    init_color(7, 500, 500, 500);
    init_pair(7, 0, 0);
    init_pair(2, COLOR_GREEN,   COLOR_BLACK);
    init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
    init_pair(4, COLOR_BLUE,    COLOR_BLACK);
    init_pair(5, COLOR_CYAN,    COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(1, 7, 0);
    
}

void n3_end_screen(void){
    endwin();
}

static inline int get_color(int r, int g, int b){
    return r > 0 ? 1 : 7;
}

static inline char get_intensity_char(int intensity){
    return sizes[9*intensity/255];
}

/* vector drawer
 */
int n3_vector_draw(std::vector<std::uint8_t> data, int width, int height){
    for (int y=0; y<height; y++){
        for (int x=0; x<width; x++){
            char intensity = get_intensity_char(data[((height-y-1)*width+x)*4+3]);
            int color = get_color(
                    data[((height-y-1)*width+x)*4],
                    data[((height-y-1)*width+x)*4+1],
                    data[((height-y-1)*width+x)*4+2]);
            attron(COLOR_PAIR(color));
            mvaddch(y, x, intensity);
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
