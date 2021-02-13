//
// Created by 朱洲 on 2020/4/24.
//

#ifndef OPENGL_LEARNING_MESH_H
#define OPENGL_LEARNING_MESH_H

#include <glm.hpp>
#include <string>
#include <vector>
#include "Material.h"

struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {

public:
    Mesh(std::vector<Vertex> _vertices,std::vector<unsigned int> _indices,std::vector<Texture> _textures);

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    void Draw(Material* material);

private:
    unsigned int VAO,VBO,EBO;

    void setupMesh();

};


#endif //OPENGL_LEARNING_MESH_H
