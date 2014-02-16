#include "gamecube.hpp"

GameCube::GameCube(glm::vec3 position, LightedColorShader *shader)
      : cube(shader),
        position(position) {
}

void GameCube::draw(glm::mat4 view, glm::mat4 proj) {
    cube.model = glm::translate(glm::mat4(1.0f), position);
    cube.draw(view, proj);
}

void GameCube::draw_rotate(glm::mat4 view, glm::mat4 proj, float rotate) {
    cube.model = glm::rotate(cube.model, rotate, glm::vec3(0.7f, 0.5f, 0.2f));
    cube.draw(view, proj);
}

void GameCube::draw_big(glm::mat4 view, glm::mat4 proj){ 
    cube.model = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -2.f));
    //cube.draw(view, proj);
}

GameCube::~GameCube() {

}

