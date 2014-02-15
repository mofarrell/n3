#include <iostream>
#include <unistd.h>

#include "renderer.h"
#include "display.h"

#define WIDTH 768
#define HEIGHT 768

static void finish(int sig) {
  n3_end_screen();
  exit(0);
}

int main (int argc, char *argv[]){

  signal(SIGINT, finish);

  Renderer renderer(WIDTH, HEIGHT);
  for (int i = 0; i < 100; i ++) {
    renderer.draw();
    sleep(1);
  }

  n3_init_screen();
  n3_draw_xy('t', 10, 10);

  while(1) {
    getch
  }

  finish(0);
  return 0;
}
