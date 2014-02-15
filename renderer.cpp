#include <stddef.h>
#include <iostream>
#include <vector>

#include "renderer.h"
#include "shader.h"

const GLchar *vertex_shader[] = {
  "#version 330\n",
  "void main(void) {\n",
  "    \n",
  "    \n",
  "}"
};

const GLchar *fragment_shader[] = {
  "#version 330\n",
  "void main() {\n",
  "    \n",
  "}"
};


Renderer::Renderer(int width, int height)
    : ctx(),
      prog(vertex_shader, fragment_shader),
      width(width),
      height(height) {
    glGenFramebuffers(1,&fbo);
    glGenRenderbuffers(1,&render_buf);
    glBindRenderbuffer(GL_RENDERBUFFER, render_buf);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, width, height);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER,fbo);
    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, render_buf);
  }


void Renderer::draw() {
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,fbo);

  // Use the shaders.
  prog();

  // draw here

  std::vector<std::uint8_t> data(width*height*4);
  //glReadBuffer(GL_COLOR_ATTACHMENT0);
  //glReadPixels(0,0,width,height,GL_BGRA,GL_UNSIGNED_BYTE,&data[0]);

  // data is valid here!!

  // Return to onscreen rendering: (not really necessary)
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);
  std::cout << "Rendered\n";
}


Renderer::~Renderer() {
  glDeleteFramebuffers(1,&fbo);
  glDeleteRenderbuffers(1,&render_buf);
}



