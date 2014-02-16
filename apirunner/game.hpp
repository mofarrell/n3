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
        glm::vec3 direction;
        void gameLoop();
        void update();
};

#endif /*GAME_HPP*/
