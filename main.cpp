#include <iostream>
#include <unistd.h>

#include "renderer.h"

#define WIDTH 768
#define HEIGHT 768

int main ()
{
  std::cout << "Hello World!\n";
  Renderer renderer(WIDTH, HEIGHT);
  for (int i = 0; i < 100; i ++) {
    renderer.draw();
    sleep(1);
  }
  std::cout << "Hello World!\n";
  return 0;
}
