#include <stddef.h>
#include <iostream>
#include <vector>

#include "renderer.h"
#include "shader.h"
#include "display.h"

const GLchar *vertex_shader[] = {
    "#version 330\n",
    "layout(location = 0) in vec3 vert;\n",
    "uniform mat4 mvp;\n",
    "void main(void) {\n",
    "    gl_Position = mvp * vec4(vert.xyz, 1.f);\n",
    "}"
};

const GLchar *fragment_shader[] = {
    "#version 330\n",
    "out vec4 fragColor;\n",
    "void main() {\n",
    "    fragColor = vec4(1.0, 0.0, 0.0, 1.0);\n",
    "}"
};

// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
};
static GLuint vertexbuffer;
static GLuint vao;
static glm::mat4 model;

Renderer::Renderer(int width, int height)
    : ctx(),
      prog(vertex_shader, fragment_shader),
      width(width),
      height(height) {
  proj = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
  view = glm::mat4(1.0f);
  model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));

  glGenFramebuffersEXT(1,&fbo);
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
  glGenRenderbuffersEXT(1,&render_buf);
  glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, render_buf);
  //std::cout << "1: " << glGetError() << std::endl;
  glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGBA8, width, height);
  //std::cout << "2: " <<  glGetError() << std::endl;
  glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, render_buf);
  // Set the list of draw buffers.
  //GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
  //glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
  //std::cout << "3: " <<  glGetError() << std::endl;

  // Always check that our framebuffer is ok
  if(glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) != GL_FRAMEBUFFER_COMPLETE)
      std::cerr << "No Framebuffer" << std::endl;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Generate 1 buffer, put the resulting identifier in vertexbuffer
  glGenBuffers(1, &vertexbuffer);

  // The following commands will talk about our 'vertexbuffer' buffer
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

  // Give our vertices to OpenGL.
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
  glVertexAttribPointer(
          0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
          3,                  // size
          GL_FLOAT,           // type
          GL_FALSE,           // normalized?
          0,                  // stride
          (void*)0            // array buffer offset
          );

  glEnableVertexAttribArray(0);
  //glDisableVertexAttribArray(0);
  glBindVertexArray(0);

  mvpLocation = glGetUniformLocation(prog, "mvp");
}


void Renderer::draw() {
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
    glViewport(0,0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  
    std::cout << "asdfdsf" << std::endl;
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(model * view * proj));

    std::cout << "asdfdsfi2" << std::endl;
    //glDrawBuffer(GL_FRAMEBUFFER_EXT);
    //std::cout  << "3.5: " << glGetError() << std::endl;

    // Use the shaders.
    prog();
    // draw here

    // 1rst attribute buffer : vertices
    //std::cout  << "3.3: " << glGetError() << std::endl;
    //std::cout  << "3.4: " << glGetError() << std::endl;
    glBindVertexArray(vao);
    // Draw the triangle !
    //std::cout  << "3.5: " << glGetError() << std::endl;
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    //std::cout  << "4: " << glGetError() << std::endl;
    glBindVertexArray(0);

    // glDisableVertexAttribArray(0);
    //std::cout  << "5: " << glGetError() << std::endl;

    std::vector<std::uint8_t> data(width*height*4);

    //glReadBuffer(GL_COLOR_ATTACHMENT0);
    //std::cout << glGetError() << std::endl;
    glReadPixels(0,0,width,height,GL_RGBA,GL_UNSIGNED_BYTE,data.data());
    //std::cout << glGetError() << std::endl;

    //printf("%d\n", data[0]);
    /*
    for (int i = 0; i < width*height*4; i ++) {
        printf("%d ", data[i]);
    }
    printf("\n");
*/
    n3_vector_draw(data, width, height);
    // data is valid here!!

    // Return to onscreen rendering: (not really necessary)
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
    ////std::cout << "Rendered\n";
}


Renderer::~Renderer() {
    glDeleteFramebuffersEXT(1,&fbo);
    glDeleteRenderbuffersEXT(1,&render_buf);
}



