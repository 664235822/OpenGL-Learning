//
// Created by 朱洲 on 2020/3/4.
//

#include "PointLight.h"

PointLight::PointLight(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) :
        position(_position),
        angles(_angles),
        color(_color) {
    constant = 1.0f;
    linear = 0.09f;
    quadratic = 0.032f;
}
