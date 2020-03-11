//
// Created by 朱洲 on 2020/3/4.
//

#ifndef OPENGL_LEARNING_POINTLIGHT_H
#define OPENGL_LEARNING_POINTLIGHT_H

#include <glm.hpp>

class PointLight {

public:
    PointLight(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));

    glm::vec3 position;
    glm::vec3 angles;
    glm::vec3 color;

    glm::vec3 direction = glm::vec3(0, 0, 1.0f);

    constexpr static float constant = 1.0f;
    constexpr static float linear = 0.09f;
    constexpr static float quadratic = 0.032f;
};


#endif //OPENGL_LEARNING_POINTLIGHT_H
