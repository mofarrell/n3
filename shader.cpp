
#include <stddef.h>
#include <iostream>

#include "shader.h"
// compiles shaders and handles them.

Shader_prog::operator GLuint() { return prog; }

void Shader_prog::operator()() { glUseProgram(prog); }

Shader_prog::~Shader_prog() {
  glDeleteProgram(prog);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}
