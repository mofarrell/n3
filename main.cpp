#include <iostream>
#include <unistd.h>
#include <time.h>

#include "renderer.h"
#include "display.h"

#define WIDTH COLS
#define HEIGHT LINES

static void finish(int sig) {
  n3_end_screen();
  exit(0);
}

int main (int argc, char *argv[]){

  signal(SIGINT, finish);

  struct timespec tim, tim2;
  tim.tv_sec = 0;
  tim.tv_nsec = 40000000L;
  
  n3_init_screen();

  Renderer renderer(WIDTH, HEIGHT);

  while(1) {
    renderer.draw();
    refresh();
    nanosleep(&tim, &tim2);
 }

  finish(0);
  return 0;
}
