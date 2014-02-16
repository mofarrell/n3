#include <iostream>
#include <unistd.h>
#include <time.h>

#include "renderer.h"
#include "display.h"
#include "apirunner/game.hpp"

static void finish(int sig) {
  n3_end_screen();
  exit(0);
}

int main (int argc, char *argv[]){

  signal(SIGINT, finish);


  n3_init_screen();
  
  Game *mygame = new Game();

  delete mygame;

  finish(0);
  return 0;
}
