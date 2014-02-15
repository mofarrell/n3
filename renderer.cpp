#include <stddef.h>
#include <iostream>
#include <vector>

#include "renderer.h"
#include "shader.h"

const GLchar *vertex_shader[] = {
  "#version 330\n",
  "layout(location = 0) in vec4 vert;\n",
  "//uniform mat4 mvp;\n",
  "void main(void) {\n",
  "    gl_Position = vec4(vert.xy, 0.f, 0.f);\n",
  "    \n",
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

    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
     
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
     
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
  }


void Renderer::draw() {
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,fbo);

  // Use the shaders.
  prog();

  // draw here
  
// 1rst attribute buffer : vertices
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glVertexAttribPointer(
         0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
               GL_FLOAT,           // type
                  GL_FALSE,           // normalized?
                     0,                  // stride
                        (void*)0            // array buffer offset
      );
   
  // Draw the triangle !
  glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
   
  glDisableVertexAttribArray(0);

  std::vector<std::uint8_t> data(width*height*4);
  glReadBuffer(GL_COLOR_ATTACHMENT0);
  glReadPixels(0,0,width,height,GL_BGRA,GL_UNSIGNED_BYTE,&data[0]);

  // data is valid here!!

  // Return to onscreen rendering: (not really necessary)
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);
  std::cout << "Rendered\n";
}


Renderer::~Renderer() {
  glDeleteFramebuffers(1,&fbo);
  glDeleteRenderbuffers(1,&render_buf);
}



