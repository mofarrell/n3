#include <stddef.h>
#include <iostream>
#include <vector>

#include "renderer.h"
#include "display.h"

Renderer::Renderer(int width, int height)
    : ctx(),
      width(width),
      height(height) {
  proj = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
  view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f));

  glGenFramebuffersEXT(1,&fbo);
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
  glGenRenderbuffersEXT(1,&render_buf);
  glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, render_buf);
  //std::cout << "1: " << glGetError() << std::endl;
  glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGBA8, width, height);
  //std::cout << "2: " <<  glGetError() << std::endl;
  glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
  glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, render_buf);

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
  cube.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f));
}

void Renderer::draw() {
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
    glViewport(0,0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cube.model = glm::rotate(cube.model, 0.05f, glm::vec3(0.1f, 0.4f, 1.0f));
  
    // draw here
    cube.draw(proj*view);


    std::vector<std::uint8_t> data(width*height*4);
    glReadPixels(0,0,width,height,GL_RGBA,GL_UNSIGNED_BYTE,data.data());

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



