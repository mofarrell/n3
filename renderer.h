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


#ifndef RENDERER_H
#define RENDERER_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/gl3ext.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl3.h>
#include "context.h"
#else
#ifdef _WIN32
  #include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glext.h>
#endif

#define GLM_FORCE_RADIANS
// glm::vec3, glm::vec4, glm::ivec4, glm::mat4
#include "glm/glm.hpp"
// glm::perspective
// glm::translate, glm::rotate, glm::scale
#include "glm/gtc/matrix_transform.hpp"
// glm::value_ptr
#include "glm/gtc/type_ptr.hpp"


#include "colorshader.h"
#include "lightedcolorshader.h"
#include "cube.h"
#include "triangle.h"

class Renderer {
 public:
  Context ctx;
  GLuint fbo, render_buf, depth_buf;
  GLuint tex_buf;
  GLuint mvpLocation;
  int width, height;
  glm::mat4 view;
  glm::mat4 proj;
  LightedColorShader lightedColorShader;
  ColorShader colorShader;
  Cube cube;
  Triangle triangle;
  void *game;

  Renderer(int width, int height, void *game);

  void draw();

  ~Renderer();
};

#endif /* RENDERER_H */

