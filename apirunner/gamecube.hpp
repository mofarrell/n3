#ifndef GAMECUBE_HPP
#define GAMECUBE_HPP

#include "../cube.h"
#include "../lightedcolorshader.h"

class GameCube {
    public:
        GameCube(glm::vec3 position, LightedColorShader *shader);
        Cube cube;
        void draw(glm::mat4 view, glm::mat4 proj);
        glm::vec3 position;
        ~GameCube();
        void cubeRender();
};

#endif /*GAMECUBE_HPP*/
