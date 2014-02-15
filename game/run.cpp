#include <curses.h>
#include <run.h>

typedef unsigned long mmask_t;

typedef struct {
  short id; /* id for multiple devices */
  int x, y, z; /* event coords */
  mmask_t bstate; /* button state bits */
}

int main () {
  quit = false;
  while (!quit) {
    /*
    Check for user input
    Check dem collisions
    Draw graphics
    (Could have sound playing
    */
  }
