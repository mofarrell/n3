
#include <stddef.h>
#include <iostream>

#include "shader.h"
// compiles shaders and handles them.

shader_prog::operator GLuint() { return prog; }

void shader_prog::operator()() { glUseProgram(prog); }

shader_prog::~shader_prog() {
  glDeleteProgram(prog);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}
