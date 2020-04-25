//
// Created by 朱洲 on 2020/4/25.
//

#ifndef OPENGL_LEARNING_MODEL_H
#define OPENGL_LEARNING_MODEL_H

#include <vector>
#include <string>
#include "Mesh.h"
#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>

class Model {

public:

    Model(std::string path);

    std::vector<Mesh> meshes;
    std::string directory;

    void Draw(Material* material);

private:

    void loadModel(std::string path);

    void processModel(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
};


#endif //OPENGL_LEARNING_MODEL_H
