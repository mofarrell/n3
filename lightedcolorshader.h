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


#ifndef LIGHTEDCOLORSHADER_H
#define LIGHTEDCOLORSHADER_H

#define GLM_FORCE_RADIANS
// glm::vec3, glm::vec4, glm::ivec4, glm::mat4
#include "glm/glm.hpp"
// glm::perspective
// glm::translate, glm::rotate, glm::scale
#include "glm/gtc/matrix_transform.hpp"
// glm::value_ptr
#include "glm/gtc/type_ptr.hpp"

#include "shader.h"

namespace _LightedColorShader {
  static const GLchar *vertex_shader[] = {
      "#version 330\n",
      "const int MAXLIGHTS = 4;\n",
      "layout(location = 0) in vec3 vertex;\n",
      "layout(location = 1) in vec3 vertexColor;\n",
      "layout(location = 2) in vec3 normal;\n",
      "out vec3 fragmentColor;\n",
      "uniform mat4 model;\n",
      "uniform mat4 view;\n",
      "uniform mat4 projection;\n",
      "uniform vec4 lightpos;\n",
      "uniform vec4 lightdir;\n",
      "uniform vec4 lightamb;\n",
      "void main(void) {\n",
      "    gl_Position = model * vec4(vertex.xyz, 1.f);\n",
      "    vec3 rot_normal = mat3(model) * normal;\n",
      "    float f = max(dot(rot_normal, normalize(lightpos.xyz - gl_Position.xyz)), 0.0f);\n",
      "    float d = max(dot(rot_normal, normalize(-lightdir.xyz)), 0.0f);\n",
      "    fragmentColor = (min(d + lightamb.rgb, vec3(1.0f,1.0f,1.0f))) * vertexColor;\n",
      "    gl_Position = projection * view * gl_Position;\n",
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

  static GLfloat lightpos[] = {10.0f, 10.0f, -50.0f, 1.0f};
  static GLfloat lightdir[] = {1.0f, -0.7f, -0.7f, 1.0f};
  static GLfloat lightamb[] = {0.2f, 0.2f, 0.2f, 1.0f};
}

class LightedColorShader {
 public:
  GLuint modelLocation;
  GLuint viewLocation;
  GLuint projectionLocation;
  GLuint lightposLocation;
  GLuint lightdirLocation;
  GLuint lightambLocation;
  glm::mat4 view;
  glm::mat4 projection;
  glm::mat4 model;
  Shader_prog prog;

  LightedColorShader()
      : prog(_LightedColorShader::vertex_shader, _LightedColorShader::fragment_shader) {
    prog();
    modelLocation = glGetUniformLocation(prog, "model");
    viewLocation = glGetUniformLocation(prog, "view");
    projectionLocation = glGetUniformLocation(prog, "projection");
    lightposLocation = glGetUniformLocation(prog, "lightpos");
    lightdirLocation = glGetUniformLocation(prog, "lightdir");
    lightambLocation = glGetUniformLocation(prog, "lightamb");

    glUniform4fv(lightposLocation, 1, _LightedColorShader::lightpos);
    glUniform4fv(lightdirLocation, 1, _LightedColorShader::lightdir);
    glUniform4fv(lightambLocation, 1, _LightedColorShader::lightamb);
  }
  
  void operator()() {
    prog();
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
  }
  

  ~LightedColorShader() {
  }
};


#endif /* LIGHTEDCOLORSHADER_H */

