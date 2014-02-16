#ifndef GAME_HPP
#define GAME_HPP
#include "gamecube.hpp"
class Game {
    public:
        Game();
        void start();
        void generateCubes(float x, float y, float z);
        ~Game();
        Player player;
        std::vector<GameCube *>GameCubeVec;
        void gameLoop(Player player);
        void moveBoardX(int dir);
        void moveBoardY(int dir);
};

#endif /*GAME_HPP*/
