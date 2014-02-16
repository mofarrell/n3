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
