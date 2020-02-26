//
// Created by 朱洲 on 2020/2/26.
//

#include "DirectionLight.h"
#include "gtx/rotate_vector.hpp"

DirectionLight::DirectionLight(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) :
        position(_position),
        angles(_angles),
        color(_color) {

    UpdateDirection();
}


void DirectionLight::UpdateDirection() {
    direction = glm::vec3(0, 0, 1.0f);
    direction = glm::rotateZ(direction, angles.z);
    direction = glm::rotateX(direction, angles.x);
    direction = glm::rotateY(direction, angles.y);
    direction *= -1.0f;
}

