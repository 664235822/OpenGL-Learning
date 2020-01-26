//
// Created by 朱洲 on 2020/1/26.
//
#ifndef OPENGL_LEARNING_SHADER_H
#define OPENGL_LEARNING_SHADER_H

#include <string>

using namespace std;

class Shader {
public:
    Shader(const char* vertexPath,const char* fragmentPath);

    void use();
private:
    string vertexString;
    string fragmentString;

    const char* vertexSource;
    const char* fragmentSource;

    unsigned int ID;//ShaderProgramID

    void checkCompileErrors(unsigned int ID,string type);
};


#endif //OPENGL_LEARNING_SHADER_H
