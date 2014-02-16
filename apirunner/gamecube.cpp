#include "gamecube.hpp"

GameCube::GameCube(float x_i, float y_i, float z_i, LightedColorShader *shader)
      : cube(shader) {
    x = x_i;
    y = y_i;
    z = -z_i;
}

void GameCube::draw(glm::mat4 view, glm::mat4 proj) {
    cube.model = glm::translate(glm::mat4(1.0f), glm::vec3(x,y,z));
    cube.draw(view, proj);
}

GameCube::~GameCube() {

}

