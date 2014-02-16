
#ifndef CUBE_H
#define CUBE_H

#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include <OpenGL/glext.h>

#include "colorshader.h"


static const GLfloat vertices[] = {
  -1.0f,-1.0f,-1.0f,
  -1.0f,-1.0f, 1.0f,
  -1.0f, 1.0f, 1.0f,
  -1.0f,-1.0f,-1.0f,
  -1.0f, 1.0f, 1.0f,
  -1.0f, 1.0f,-1.0f,

  1.0f, 1.0f, 1.0f,
  1.0f,-1.0f,-1.0f,
  1.0f, 1.0f,-1.0f,
  1.0f,-1.0f,-1.0f,
  1.0f, 1.0f, 1.0f,
  1.0f,-1.0f, 1.0f,

  1.0f,-1.0f, 1.0f,
  -1.0f,-1.0f,-1.0f,
  1.0f,-1.0f,-1.0f,
  1.0f,-1.0f, 1.0f,
  -1.0f,-1.0f, 1.0f,
  -1.0f,-1.0f,-1.0f,

  1.0f, 1.0f, 1.0f,
  1.0f, 1.0f,-1.0f,
  -1.0f, 1.0f,-1.0f,
  1.0f, 1.0f, 1.0f,
  -1.0f, 1.0f,-1.0f,
  -1.0f, 1.0f, 1.0f,

  1.0f, 1.0f,-1.0f,
  -1.0f,-1.0f,-1.0f,
  -1.0f, 1.0f,-1.0f,
  1.0f, 1.0f,-1.0f,
  1.0f,-1.0f,-1.0f,
  -1.0f,-1.0f,-1.0f,

  -1.0f, 1.0f, 1.0f,
  -1.0f,-1.0f, 1.0f,
  1.0f,-1.0f, 1.0f,
  1.0f, 1.0f, 1.0f,
  -1.0f, 1.0f, 1.0f,
  1.0f,-1.0f, 1.0f
};

static const GLfloat colors[] = {
  1.0f,  0.0f,  0.0f,
  1.0f,  0.0f,  0.0f,
  1.0f,  0.0f,  0.0f,
  1.0f,  0.0f,  0.0f,
  1.0f,  0.0f,  0.0f,
  1.0f,  0.0f,  0.0f,

  0.0f,  1.0f,  0.0f,
  0.0f,  1.0f,  0.0f,
  0.0f,  1.0f,  0.0f,
  0.0f,  1.0f,  0.0f,
  0.0f,  1.0f,  0.0f,
  0.0f,  1.0f,  0.0f,

  0.0f,  0.0f,  1.0f,
  0.0f,  0.0f,  1.0f,
  0.0f,  0.0f,  1.0f,
  0.0f,  0.0f,  1.0f,
  0.0f,  0.0f,  1.0f,
  0.0f,  0.0f,  1.0f,

  1.0f,  1.0f,  0.0f,
  1.0f,  1.0f,  0.0f,
  1.0f,  1.0f,  0.0f,
  1.0f,  1.0f,  0.0f,
  1.0f,  1.0f,  0.0f,
  1.0f,  1.0f,  0.0f,

  0.0f,  1.0f,  1.0f,
  0.0f,  1.0f,  1.0f,
  0.0f,  1.0f,  1.0f,
  0.0f,  1.0f,  1.0f,
  0.0f,  1.0f,  1.0f,
  0.0f,  1.0f,  1.0f,

  1.0f,  0.0f,  1.0f,
  1.0f,  0.0f,  1.0f,
  1.0f,  0.0f,  1.0f,
  1.0f,  0.0f,  1.0f,
  1.0f,  0.0f,  1.0f,
  1.0f,  0.0f,  1.0f,
};

class Cube {
 public:
  GLuint vbo;
  GLuint cbo;
  GLuint vao;
  ColorShader shader;
  glm::mat4 model;

  Cube () : shader() {
    model = glm::mat4(1.0f);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


    //////////////////////////////
    // Vertice coords
    //////////////////////////////
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vbo);

    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
            );
    glEnableVertexAttribArray(0);
    //////////////////////////////
    // Color coords
    //////////////////////////////
    glGenBuffers(1, &cbo);

    glBindBuffer(GL_ARRAY_BUFFER, cbo);

    // Give our colors to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(
            1,                  // attribute 1. No particular reason for 1, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
            );
    glEnableVertexAttribArray(1);


    glBindVertexArray(0);
  }

  void draw(glm::mat4 viewProjection) {
    shader.vp = viewProjection;
    shader.model = model;
    shader();

    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/sizeof(GLfloat)/3); // Starting from vertex 0; vertices total -> 1 triangle

    glBindVertexArray(0);
  }

  ~Cube () {
  }
};

#endif /* CUBE_H */

