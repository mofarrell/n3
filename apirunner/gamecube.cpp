#include "gamecube.hpp"

GameCube::GameCube(glm::vec3 position, LightedColorShader *shader)
      : cube(shader),
        position(position) {
}

void GameCube::draw(glm::mat4 view, glm::mat4 proj) {
    cube.model = glm::translate(glm::mat4(1.0f), position);
    cube.draw(view, proj);
}

GameCube::~GameCube() {

}

