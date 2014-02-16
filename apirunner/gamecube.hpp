#ifndef GAMECUBE_HPP
#define GAMECUBE_HPP

#include "../cube.h"
#include "../lightedcolorshader.h"

class GameCube {
    public:
        GameCube(float x, float y, float z, LightedColorShader *shader);
        Cube cube;
        void draw(glm::mat4 view, glm::mat4 proj);
        float x, y, z;
        ~GameCube();
        void cubeRender();
};

#endif /*GAMECUBE_HPP*/
