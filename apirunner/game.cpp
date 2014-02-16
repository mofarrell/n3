#include <vector>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "../cube.h"
#include "player.hpp"
#include "game.hpp"

#define MAX_WIDTH 323
#define MAX_NUM_CUBES 100

Game::Game() : GameCubeVec() {}

void Game::start() {
    player = Player::Player();
    Game::generateCubes(player.x,player.y,player.z);
    Game::gameLoop(player);
}

void Game::generateCubes(float x, float y, float z) {
    int i = MAX_NUM_CUBES;
    float curr_z = 20.0f;
    while (i > 0){
        srand (time(NULL));
        int num_on_plane = (rand() % 10);
        i -= num_on_plane;
        curr_z += (float)i*80.0/100.0;
        
        float rand_x = float(rand() % MAX_WIDTH);
        float rand_y = float(rand() % MAX_WIDTH);
        std::printf("%.2f %.2f %.2f\n", rand_x, rand_y, curr_z);
        GameCubeVec.push_back(new GameCube(rand_x, rand_y, curr_z));
    }
    /* Render all cubes */
    for (std::vector<GameCube *>::iterator it = GameCubeVec.begin();
         it != GameCubeVec.end(); 
         ++it) {
        /* render(it); */
    }
}

void Game::gameLoop(Player player){
    player.move(player.x, player.y, player.z);
    /*StartTimer */
    /*incrementLevel */
    /* Make 3D */
}
void Game::moveBoardX(int dir) {
    for (std::vector<GameCube *>::iterator it = GameCubeVec.begin();
         it != GameCubeVec.end(); 
         ++it) {
        (*it)->x += dir % MAX_WIDTH;
    }
}
void Game::moveBoardY(int dir) {
    for (std::vector<GameCube *>::iterator it = GameCubeVec.begin();
         it != GameCubeVec.end(); 
         ++it) {
        (*it)->y += dir % MAX_WIDTH;
    }
}
