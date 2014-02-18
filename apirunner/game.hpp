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

#ifndef GAME_HPP
#define GAME_HPP
#include "gamecube.hpp"
#include "player.hpp"
#include "../renderer.h"
#include "../display.h"
#include "../triangle.h"
#include "../obj.h"

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
        Obj obj;
};

#endif /*GAME_HPP*/
