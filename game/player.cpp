#include Player.h
Player::Player (int id, float startX, float startY, float startZ) {
  x = startX;
  y = startY;
  z = startZ;
  //Render
  isAlive = true;
}

void Player::Respawn(float startX, float startY, float startZ) {
  //Render
  isAlive = true;
}

void Player::Render() {
  //Render
}

void Player::Move() {
  //Move forward
}

void Player::Rotate(int direction) {
  //rotate Left Right Down Up
}

void Player::Jump() {
  //Jump
}

void Player::Shoot() {
  //Fire gun
}

void Player::Pwned() {
  //Hide/Destroy player
}
