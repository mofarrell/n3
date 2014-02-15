#include <stddef.h>
#include <iostream>
#include <vector>

#include "renderer.h"
#include "shader.h"

const GLchar *vertex_shader[] = {
  "void main(void) {\n",
  "    gl_Position = ftransform();\n",
  "    gl_FrontColor = gl_Color;\n",
  "}"
};

const GLchar *color_shader[] = {
  "void main() {\n",
  "    gl_FragColor = gl_Color;\n",
  "}"
};

Renderer::Renderer(int width, int height)
    : prog(vertex_shader, color_shader),
      width(width),
      height(height) {
    std::cout << "here one!\n";
    glGenFramebuffers(1,&fbo);
    glGenRenderbuffers(1,&render_buf);
    glBindRenderbuffer(GL_RENDERBUFFER, render_buf);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, width, height);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER,fbo);
    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, render_buf);
    std::cout << "here one\n";
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



