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


#ifndef SHADER_H
#define SHADER_H

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

#include <iostream>

// Things defined in header so that templates work.

class Shader_prog {
  GLuint vertex_shader, fragment_shader, prog;

  template <int N>
    GLuint compile(GLuint type, char const *(&source)[N]) {
      GLuint shader = glCreateShader(type);
      glShaderSource(shader, N, source, NULL);
      glCompileShader(shader);
      GLint compiled;
      glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
      if (!compiled) {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        std::string log(length, ' ');
        glGetShaderInfoLog(shader, length, &length, &log[0]);
        throw std::logic_error(log);
        return false;
      }
      return shader;
    }
 public:
  template <int N, int M>
    Shader_prog(GLchar const *(&v_source)[N], GLchar const *(&f_source)[M]) {
      vertex_shader = compile(GL_VERTEX_SHADER, v_source);
      fragment_shader = compile(GL_FRAGMENT_SHADER, f_source);
      prog = glCreateProgram();
      glAttachShader(prog, vertex_shader);
      glAttachShader(prog, fragment_shader);
      glLinkProgram(prog);
    }
  operator GLuint();
  void operator()();
  ~Shader_prog();
};

#endif /* SHADER_H */

