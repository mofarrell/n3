/*The MIT License (MIT)
 *
 *Copyright (c) 2014 Michael O'Farrell, Bram Wasti
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy
 *of this software and associated documentation files (the "Software"), to deal
 *in the Software without restriction, including without limitation the rights
 *to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *copies of the Software, and to permit persons to whom the Software is
 *furnished to do so, subject to the following conditions:
 *
 *The above copyright notice and this permission notice shall be included in
 *all copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *THE SOFTWARE.
 *
 */

#include <stddef.h>
#include <iostream>
#include <vector>

#include "renderer.h"
#include "display.h"
#include "apirunner/game.hpp"

Renderer::Renderer(int width, int height, void *game)
    : ctx(),
      width(width),
      height(height),
      cube(&lightedColorShader),
      triangle(&colorShader),
      game(game) {
  proj = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 50.f);
  view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f));

  glGenFramebuffersEXT(1,&fbo);
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
  //glGenRenderbuffersEXT(1,&render_buf);
  //glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, render_buf);
  glGenTextures(1, &tex_buf);
  glBindTexture(GL_TEXTURE_2D, tex_buf);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
    GL_UNSIGNED_BYTE, 0);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glFramebufferTexture(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0,
    tex_buf, 0);
  //std::cout << "1: " << glGetError() << std::endl;
  //glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGBA8, width, height);
  //std::cout << "2: " <<  glGetError() << std::endl;
  //glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
  //glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, render_buf);

  if (1) {
    glGenRenderbuffersEXT(1, &depth_buf);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depth_buf);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, width, height);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depth_buf);
    glEnable(GL_DEPTH_TEST);
  }

  // Always check that our framebuffer is ok
  if(glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) != GL_FRAMEBUFFER_COMPLETE)
      std::cerr << "No Framebuffer" << std::endl;
  cube.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
  triangle.model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f,0.5f,0.5f));
  triangle.model = glm::translate(triangle.model, glm::vec3(0.f, -1.5f, 0.f));
  triangle.model = glm::rotate(triangle.model, 1.1f, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Renderer::draw() {
    
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
    glViewport(0,0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cube.model = glm::rotate(cube.model, 0.05f, glm::vec3(0.5f, 0.2f, 1.0f));
  
    ((Game *)game)->render();

    std::vector<std::uint8_t> data(width*height*4);
    //glReadPixels(0,0,width,height,GL_RGBA,GL_UNSIGNED_BYTE,data.data());
    glBindTexture(GL_TEXTURE_2D, tex_buf);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());

    // data is valid here!!
    n3_vector_draw(data, width, height);

    // Return to onscreen rendering: (not really necessary)
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
    //std::cout << "Rendered\n";
}


Renderer::~Renderer() {
  glDeleteFramebuffersEXT(1,&fbo);
  glDeleteRenderbuffersEXT(1,&render_buf);
  glDeleteRenderbuffersEXT(1,&depth_buf);
}



