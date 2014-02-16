#ifndef GAME_HPP
#define GAME_HPP
#include "gamecube.hpp"
#include "player.hpp"
#include "../renderer.h"
#include "../display.h"
#include "../triangle.h"

class Game {
    public:
        Game();
        std::vector<GameCube *> GameCubeVec;
        void renderCubes();
        void renderMenu();
        void renderScore();
        void render();
        ~Game();
        Player player;
        Renderer renderer;
        glm::vec3 direction;
        void gameLoop();
        void update(glm::vec2 delta);
        bool isDead;
        long score;
        long level;
        void gameOver();
        glm::vec3 random_vec();
};

#endif /*GAME_HPP*/
