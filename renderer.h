
#ifndef RENDERER_H
#define RENDERER_H

#include <OpenGL/gl3.h>
#include "shader.h"

class renderer {
  GLuint fbo, render_buf;
  shader_prog prog;
  int width, height;

  renderer(int width, int height);

  void draw();

  ~renderer();
};

#endif /* RENDERER_H */

