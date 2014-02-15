
#ifndef RENDERER_H
#define RENDERER_H

#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include <OpenGL/glext.h>
#include "shader.h"
#include "context.h"


#define GLM_FORCE_RADIANS
// glm::vec3, glm::vec4, glm::ivec4, glm::mat4
#include "glm/glm.hpp"
// glm::perspective
// glm::translate, glm::rotate, glm::scale
#include "glm/gtc/matrix_transform.hpp"
// glm::value_ptr
#include "glm/gtc/type_ptr.hpp"

class Renderer {
 public:
  Context ctx;
  GLuint fbo, render_buf;
  Shader_prog prog;
  GLuint mvpLocation;
  int width, height;
  glm::mat4 view;
  glm::mat4 proj;

  Renderer(int width, int height);

  void draw();

  ~Renderer();
};

#endif /* RENDERER_H */

