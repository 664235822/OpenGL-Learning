//
// Created by 朱洲 on 2020/2/17.
//

#ifndef OPENGL_LEARNING_MATERIAL_H
#define OPENGL_LEARNING_MATERIAL_H

#include "Shader.h"

#include <glm.hpp>

class Material {

public:
    Material(Shader *shader, glm::vec3 _ambient, unsigned int _diffuse, unsigned int _specular, float _shininess);

    Shader *shader;
    glm::vec3 ambient;
    unsigned int diffuse;
    unsigned int specular;
    float shininess;

    enum Slot{
        Diffuse,
        Specular
    };

    void setUniform3f(const char *paramNameString, glm::vec3 param);

    void setUniform1f(const char *paramNameString, float param);

    void setUniform1i(const char *paramNameString, unsigned int slot);

};


#endif //OPENGL_LEARNING_MATERIAL_H
