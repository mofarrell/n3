#ifndef GAME_HPP
#define GAME_HPP
#include "gamecube.hpp"
#include "player.hpp"
#include "../renderer.h"
#include "../display.h"

class Game {
    public:
        Game();
        std::vector<GameCube *> GameCubeVec;
        void renderCubes();
        void render();
        ~Game();
        Player player;
        Renderer renderer;
        void gameLoop();
        void moveBoardX(int dir);
        void moveBoardY(int dir);
};

#endif /*GAME_HPP*/
