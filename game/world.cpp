#include <World.h>

World::World(int inputWidth, int inputHeight) {
  const int World::WIDTH = inputWidth;
  const int World::HEIGHT = inputHeight;
  height = inputHeight;
  int *board[World::WIDTH];
  for (int i = 0; i < World::WIDTH; i++) {
    board[i] = new int[World::HEIGHT];
  }
}
