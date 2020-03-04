//
// Created by 朱洲 on 2020/3/4.
//

#ifndef OPENGL_LEARNING_SPOTLIGHT_H
#define OPENGL_LEARNING_SPOTLIGHT_H

#include <glm.hpp>

class SpotLight {

public:
    SpotLight(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));

    glm::vec3 position;
    glm::vec3 angles;
    glm::vec3 color;

    glm::vec3 direction = glm::vec3(0, 0, 1.0f);

    float cosInnerPhy = 0.9f;
    float cosOuterPhy = 0.85f;

    void UpdateDirection();
};


#endif //OPENGL_LEARNING_SPOTLIGHT_H
