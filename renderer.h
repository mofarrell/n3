
#ifndef RENDERER_H
#define RENDERER_H

#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include <OpenGL/glext.h>

#define GLM_FORCE_RADIANS
// glm::vec3, glm::vec4, glm::ivec4, glm::mat4
#include "glm/glm.hpp"
// glm::perspective
// glm::translate, glm::rotate, glm::scale
#include "glm/gtc/matrix_transform.hpp"
// glm::value_ptr
#include "glm/gtc/type_ptr.hpp"


#include "context.h"
#include "colorshader.h"
#include "lightedcolorshader.h"
#include "cube.h"
#include "triangle.h"

class Renderer {
 public:
  Context ctx;
  GLuint fbo, render_buf, depth_buf;
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

