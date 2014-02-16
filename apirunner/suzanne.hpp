#ifndef SUZANNE_HPP
#define SUZANNE_HPP

#include "../cube.h"
#include "../lightedcolorshader.h"

class Suzanne {
    public:
        Suzanne(glm::vec3 position, LightedColorShader *shader);
        Cube cube;
        void draw(glm::mat4 view, glm::mat4 proj);
        glm::vec3 position;
        ~GameCube();
        void cubeRender();
};

#endif /*SUZANNE_HPP*/

