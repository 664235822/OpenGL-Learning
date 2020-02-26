//
// Created by 朱洲 on 2020/2/26.
//

#ifndef OPENGL_LEARNING_DIRECTIONLIGHT_H
#define OPENGL_LEARNING_DIRECTIONLIGHT_H

#include <glm.hpp>

class DirectionLight {

public:
    DirectionLight(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));

    glm::vec3 position;
    glm::vec3 angles;
    glm::vec3 color;

    glm::vec3 direction = glm::vec3(0, 0, 1.0f);

    void UpdateDirection();
};


#endif //OPENGL_LEARNING_DIRECTIONLIGHT_H
