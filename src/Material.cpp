//
// Created by 朱洲 on 2020/2/17.
//

#include "Material.h"
#include <glew.h>

Material::Material(Shader *_shader, glm::vec3 _ambient, unsigned int _diffuse, glm::vec3 _specular, float _shininess) :
        shader(_shader),
        ambient(_ambient),
        diffuse(_diffuse),
        specular(_specular),
        shininess(_shininess) {

}

void Material::setUniform3f(const char *paramNameString, glm::vec3 param) {
    glUniform3f(glGetUniformLocation(shader->ID, paramNameString), param.x, param.y, param.z);
}

void Material::setUniform1f(const char *paramNameString, float param) {
    glUniform1f(glGetUniformLocation(shader->ID, paramNameString), param);
}

void Material::setUniform1i(const char *paramNameString, unsigned int slot) {
    glUniform1i(glGetUniformLocation(shader->ID, paramNameString), slot);
}

void Material::use() {
    setUniform3f("material.ambient", ambient);
    setUniform1i("material.diffuse", 0);
    setUniform3f("material.specular", specular);
    setUniform1f("material.shininess", shininess);
}


