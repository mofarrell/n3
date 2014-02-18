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


#ifndef COLORSHADER_H
#define COLORSHADER_H

#define GLM_FORCE_RADIANS
// glm::vec3, glm::vec4, glm::ivec4, glm::mat4
#include "glm/glm.hpp"
// glm::perspective
// glm::translate, glm::rotate, glm::scale
#include "glm/gtc/matrix_transform.hpp"
// glm::value_ptr
#include "glm/gtc/type_ptr.hpp"

#include "shader.h"

namespace _ColorShader {
  static const GLchar *vertex_shader[] = {
      "#version 330\n",
      "layout(location = 0) in vec3 vertex;\n",
      "layout(location = 1) in vec3 vertexColor;\n",
      "out vec3 fragmentColor;\n",
      "uniform mat4 model;\n",
      "uniform mat4 vp;\n",
      "void main(void) {\n",
      "    gl_Position = vp * model * vec4(vertex.xyz, 1.f);\n",
      "    fragmentColor = vertexColor;\n",
      "}"
  };

  static const GLchar *fragment_shader[] = {
      "#version 330\n",
      "in vec3 fragmentColor;\n",
      "out vec4 color;\n",
      "void main() {\n",
      "    color = vec4(fragmentColor, 1.0); // (pow(fragmentColor.r,2) + pow(fragmentColor.g,2) + pow(fragmentColor.b,2))/3.0);\n",
      "}"
  };
}

class ColorShader {
 public:
  GLuint modelLocation;
  GLuint vpLocation;
  glm::mat4 vp;
  glm::mat4 model;
  Shader_prog prog;

  ColorShader()
      : prog(_ColorShader::vertex_shader, _ColorShader::fragment_shader) {
    prog();
    modelLocation = glGetUniformLocation(prog, "model");
    vpLocation = glGetUniformLocation(prog, "vp");
  }
  
  void operator()() {
    prog();
    glUniformMatrix4fv(vpLocation, 1, GL_FALSE, glm::value_ptr(vp));
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
  }
  

  ~ColorShader() {
  }
};


#endif /* COLORSHADER_H */

