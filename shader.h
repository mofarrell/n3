
#ifndef SHADER_H
#define SHADER_H

class shader_prog {
    GLuint vertex_shader, fragment_shader, prog;

    template <int N>
    GLuint compile(GLuint type, char const *(&source)[N]);
public:
    template <int N, int M>
    shader_prog(GLchar const *(&v_source)[N], GLchar const *(&f_source)[M]);

    operator GLuint();
    void operator()();
    ~shader_prog();
};

#endif /* SHADER_H */

