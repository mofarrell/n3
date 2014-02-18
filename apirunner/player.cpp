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

#include "player.hpp"

void Player::collision(float p_x, float p_y, float p_z,
    float x_1, float x_2, float y_1, float y_2, float z_1, float z_2) {
    if ((p_x > x_1 && p_x < x_2)
       && (p_z < z_1 && p_z > z_2)
       && (p_y > y_1 && p_y < y_2)) {
    
        Player::kill_player();

    }
}

void Player::move(float x, float y, float z){
    //some translation (mebe rotation) code here
    /*
    getch();
    if left
        moveBoardX(1);
    if right
        moveBoardX(-1);
    if down
        moveBoardY(1);
    if up
        moveBoardY(-1);
    */
    //this->Collision(this->x, this->y, this->z);
}

void Player::checkCollisions() {
    //
}

void Player::kill_player() {
    this->isDead = true;
    Player::game_over();    
}

void Player::game_over() {
    return;
}

Player::Player(){
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    level = 1;     
}
