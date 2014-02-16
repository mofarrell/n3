#include <vector>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "../cube.h"
#include "game.hpp"

#define MAX_WIDTH 50
#define MAX_NUM_CUBES 1000

#define WIDTH COLS
#define HEIGHT LINES

Game::Game()
      : GameCubeVec(), renderer(WIDTH, HEIGHT, this), direction(0.0f, 0.0f,0.1f) {
    int i = MAX_NUM_CUBES;
    float curr_z = 20.0f;
    srand (time(NULL));
    while (i > 0){
        int num_on_plane = (rand() % 10);
        i -= num_on_plane;
        curr_z += (float)i*80.0/100.0;
        curr_z /= 2;
        
        float rand_x = float(rand() % MAX_WIDTH - (MAX_WIDTH/2));
        float rand_y = float(rand() % MAX_WIDTH - (MAX_WIDTH/2));
        float rand_z = (float)(rand() % 100);
        //std::printf("%.2f %.2f %.2f\n", rand_x, rand_y, curr_z);
        GameCubeVec.push_back(new GameCube(glm::vec3(rand_x, rand_y, -rand_z), &renderer.lightedColorShader));
    }
    
    gameLoop();
}

Game::~Game() {
    for (std::vector<GameCube *>::iterator it = GameCubeVec.begin();
         it != GameCubeVec.end(); 
         ++it) {
        delete (*it);
    }
}

void Game::renderCubes() {
    /* Render all cubes */
    for (std::vector<GameCube *>::iterator it = GameCubeVec.begin();
         it != GameCubeVec.end(); 
         ++it) {
        (*it)->draw(renderer.view, renderer.proj);
    }
}

void Game::render() {
  renderCubes();
} 


void Game::gameLoop(){
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 500000L;
 

    while(1) {
      //renderer.view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, blah));
      renderer.draw();
      refresh();
      nanosleep(&tim, &tim2);
      update();
    }
    //player.move(player.x, player.y, player.z);
    /*StartTimer */
    /*incrementLevel */
    /* Make 3D */
}

void Game::update() {
    for (std::vector<GameCube *>::iterator it = GameCubeVec.begin();
         it != GameCubeVec.end(); 
         ++it) {
        (*it)->position += direction;
        (*it)->position.z = ((*it)->position.z > 0.0f) ? -100.0f : ((*it)->position.z);
    }
}


