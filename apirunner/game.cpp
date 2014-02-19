/*The MIT License (MIT)
 *
 *Copyright (c) 2014 Michael O'Farrell, Bram Wasti
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy
 *of this software and associated documentation files (the "Software"), to deal
 *in the Software without restriction, including without limitation the rights
 *to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *copies of the Software, and to permit persons to whom the Software is
 *furnished to do so, subject to the following conditions:
 *
 *The above copyright notice and this permission notice shall be included in
 *all copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *THE SOFTWARE.
 *
 */

#include <vector>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "../cube.h"
#include "game.hpp"
#include "../objloader.hpp"
#include "../obj.h"

#define MAX_WIDTH 50
#define MAX_NUM_CUBES 500

#define WIDTH COLS
#define HEIGHT LINES

WINDOW *menu_win;

Game::Game()
      : GameCubeVec(),
        renderer(WIDTH, HEIGHT, this),
        direction(0.0f, 0.0f,0.2f),
        obj(&renderer.lightedColorShader, "suzanne.obj"){
    obj.model = glm::translate(glm::mat4(1.f), glm::vec3(0.f,0.f,-1.5f));
    isDead = true;
    score = 0;
    level = 0;
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
        float rand_z = (float)(rand() % 50);
        //std::printf("%.2f %.2f %.2f\n", rand_x, rand_y, curr_z);
        GameCubeVec.push_back(new GameCube(glm::vec3(rand_x, rand_y, -rand_z), &renderer.lightedColorShader));
    }
    //menu_win = initscr();
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
    score++;
}

float rot_curr;

void Game::renderMenu() {
    /* CONNELLS SHIT HERE */
    /*for (std::vector<GameCube *>::iterator it = GameCubeVec.begin();
         it != GameCubeVec.end(); 
         ++it) {
        (*it)->draw_big(renderer.view, renderer.proj);

    } */
   obj.model = glm::rotate(obj.model, .001f, glm::vec3(0.f,1.0f,0.f));
    obj.draw(renderer.view, renderer.proj); rot_curr = fmod((rot_curr+.005),(2*3.1415));
//    GameCubeVec[0]->draw_big(renderer.view, renderer.proj);
  //  GameCubeVec[0]->draw_rotate(renderer.view, renderer.proj, rot_curr);
    //for (int j =0; j < 32; j++) {
      
      //mvaddstr(j+10, 10, menu[j]);
   // }
    //refresh();
}

void Game::renderScore(){
    /* CONNELLS SHIT HERE */
    //(void*) figletwrapper("hello");
}


void Game::render() {
    if (isDead) {
        renderMenu();
    } else {
        renderCubes();
        //refresh();
    }
    renderScore();
    
} 

void Game::gameOver(){
    isDead = true;
    score = 0;
}

void Game::gameLoop(){
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 500000L;
 
    glm::vec2 delta;

    while(1) {
      //renderer.view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, blah));
      int c = getch();
      delta = glm::vec2(0.0f,0.0f);
      float diff = 1.0f;
      switch(c) {
        case('h'):
        case('a'):
        case(KEY_LEFT):
            delta.x += diff;
            break;
        case('l'):
        case('d'):
        case(KEY_RIGHT):
            delta.x -= diff;
            break;            
        case('k'):
        case('w'):
        case(KEY_UP):
            delta.y -= diff;
            break;
        case('j'):
        case('s'):
        case(KEY_DOWN):
            delta.y += diff;
            break;
        case ' ':
            isDead = isDead ? false : true;
            break;
      }

      renderer.draw();
      //refresh();
      nanosleep(&tim, &tim2);
      update(delta);
      level++;
    }
    //player.move(player.x, player.y, player.z);
    /*StartTimer */
    /*incrementLevel */
    /* Make 3D */
}

glm::vec3 Game::random_vec() {
        float rand_x = float(rand() % (MAX_WIDTH) - (MAX_WIDTH/2));
        float rand_y = float(rand() % (MAX_WIDTH) - (MAX_WIDTH/2));
        float det_z = -50.0f;
        return glm::vec3(rand_x, rand_y, det_z);
}

void Game::update(glm::vec2 delta) {
    for (std::vector<GameCube *>::iterator it = GameCubeVec.begin();
         it != GameCubeVec.end(); 
         ++it) {
        direction.x = delta.x;
        direction.y = delta.y;
        if (isDead)
            continue;
        (*it)->position += direction;
        (*it)->position = ((*it)->position.z > 0.0f) ? random_vec() : ((*it)->position);
        if ((*it)->position.z > -0.2f) {
            if (((*it)->position.x > -2.f) && ((*it)->position.x < 2.f) &&
                ((*it)->position.y > -2.f) && ((*it)->position.y < 2.f)) {
                this->gameOver();
            }
        }

        //(*it)->position.x = ((*it)->position.x > 100.f) ? -100.0f : ((*it)->position.x);
        //(*it)->position.y = ((*it)->position.y > 0.0f) ? -100.0f : ((*it)->position.y);
    }
}


