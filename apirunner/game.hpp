#ifndef GAME_HPP
#define GAME_HPP
#include "gamecube.hpp"
class Game {
    public:
        Game();
        void start();
        std::vector<GameCube *> GameCubeVec;
        void generateCubes(float x, float y, float z);
        ~Game();
        Player player;
        void gameLoop(Player player);
        void moveBoardX(int dir);
        void moveBoardY(int dir);
};

#endif /*GAME_HPP*/
