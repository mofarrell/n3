
#ifndef RENDERER_H
#define RENDERER_H

#include <OpenGL/gl3.h>
#include "shader.h"
#include "context.h"

class Renderer {
 public:
  Context ctx;
  GLuint fbo, render_buf;
  Shader_prog prog;
  int width, height;

  Renderer(int width, int height);

  void draw();

  ~Renderer();
};

#endif /* RENDERER_H */

