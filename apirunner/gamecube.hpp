#ifndef GAMECUBE_HPP
#define GAMECUBE_HPP

class GameCube {
    public:
        GameCube(float x, float y, float z);
        float x, y, z;
        float width;
        ~GameCube();
        void cubeRender();
};

#endif /*GAMECUBE_HPP*/
