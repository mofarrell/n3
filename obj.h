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

#ifndef OBJ_H
#define OBJ_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/gl3ext.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl3.h>
#else
#ifdef _WIN32
  #include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glext.h>
#endif



#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include "lightedcolorshader.h"
#include "objloader.hpp"

class Obj {
 public:
  GLuint vbo;
  GLuint cbo;
  GLuint nbo;
  GLuint vao;
  LightedColorShader *shader;
  glm::mat4 model;
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec2> uvs;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec3> colors;
  Obj (LightedColorShader *shader, const char *path) : shader(shader) {
    model = glm::mat4(1.0f);

    loadOBJ(path, vertices, uvs, normals);

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
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
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



    for (std::vector<glm::vec3>::iterator it = vertices.begin(); it!= vertices.end(); ++it){
        colors.push_back(glm::vec3(1.f,1.f,1.f));
    }

    // Give our colors to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(
            1,                  // attribute 1. No particular reason for 1, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
            );
    glEnableVertexAttribArray(1);
    //////////////////////////////
    // Normal vectors
    //////////////////////////////
    glGenBuffers(1, &nbo);

    glBindBuffer(GL_ARRAY_BUFFER, nbo);

    // Give our colors to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(
            2,                  // attribute 2. No particular reason for 2, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
            );
    glEnableVertexAttribArray(2);


    glBindVertexArray(0);
  }

  void draw(glm::mat4 view, glm::mat4 projection) {
    shader->view = view;
    shader->projection = projection;
    shader->model = model;
    (*shader)();

    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size()); // Starting from vertex 0; vertices total -> 1 triangle

    glBindVertexArray(0);
  }

  ~Obj () {
  }
};

#endif /* OBJ_H */

