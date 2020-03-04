//
// Created by 朱洲 on 2020/3/4.
//

#include "SpotLight.h"
#include "gtx/rotate_vector.hpp"

SpotLight::SpotLight(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) :
        position(_position),
        angles(_angles),
        color(_color) {

    UpdateDirection();
}

void SpotLight::UpdateDirection() {
    direction = glm::vec3(0, 0, 1.0f);
    direction = glm::rotateZ(direction, angles.z);
    direction = glm::rotateX(direction, angles.x);
    direction = glm::rotateY(direction, angles.y);
    direction *= -1.0f;
}
