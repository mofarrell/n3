
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

class ColorShader {
 public:
  GLuint modelLocation;
  GLuint vpLocation;
  glm::mat4 vp;
  glm::mat4 model;
  Shader_prog prog;

  ColorShader()
      : prog(vertex_shader, fragment_shader) {
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

