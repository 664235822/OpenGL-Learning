#include <glew.h>
#include <glfw3.h>
#include <cmath>
#include "src/Mesh.h"
#include "src/Model.h"
#include "src/Shader.h"
#include "src/Camera.h"
#include "src/Material.h"
#include "src/DirectionLight.h"
#include "src/PointLight.h"
#include "src/SpotLight.h"

#define STB_IMAGE_IMPLEMENTATION

#include "src/stb_image.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
};

void processInput(GLFWwindow *window);

void mouse_callback(GLFWwindow *window, double xPos, double yPos);

unsigned int LoadImageToGPU(const char *filename, GLint internalFormat, GLenum format, int textureSlot);

//相机
Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));

float lastX, lastY;
bool firstMouse = true;

int main() {
    //初始化GLFW
    if (!glfwInit()) {
        printf("Init GLFW Failed");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //创建GLFW窗口
    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //初始化GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        printf("Init GLEW Failed");
        glfwTerminate();
        return -1;
    }

    //视口
    glViewport(0, 0, 800, 600);

    //深度缓冲
    glEnable(GL_DEPTH_TEST);

    //鼠标显示
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    //创建模型
    Model *model = new Model("../model/nanosuit.obj");
    //创建着色器
    Shader *myShader = new Shader("../shader/vertexShader.vert", "../shader/fragmentShader.frag");
    //创建材质球
    Material *myMaterial = new Material(myShader,
                                        glm::vec3(1.0f, 1.0f, 1.0f),
                                        LoadImageToGPU("../img/container2.png", GL_RGBA, GL_RGBA, 0),
                                        LoadImageToGPU("../img/container2_specular.png", GL_RGBA, GL_RGBA, 1),
                                        32.0f);
    //创建平行光
    DirectionLight *lightD = new DirectionLight(glm::vec3(10.0f, 10.0f, -5.0f),
                                                glm::vec3(glm::radians(45.0f), glm::radians(45.0f),
                                                          glm::radians(45.0f)));
    //创建点光源
    PointLight *lightP0 = new PointLight(glm::vec3(1.0f, 0, 0),
                                         glm::vec3(0, 0, 0),
                                         glm::vec3(1.0f, 0, 0));
    PointLight *lightP1 = new PointLight(glm::vec3(0, 1.0f, 0),
                                         glm::vec3(0, 0, 0),
                                         glm::vec3(0, 1.0f, 0));
    PointLight *lightP2 = new PointLight(glm::vec3(0, 0, 1.0f),
                                         glm::vec3(0, 0, 0),
                                         glm::vec3(0, 0, 1.0f));
    PointLight *lightP3 = new PointLight(glm::vec3(1.0f, 1.0f, 1.0f),
                                         glm::vec3(0, 0, 0));

    //创建聚光源
    SpotLight *lightS = new SpotLight(glm::vec3(0.0f, 5.0f, 0.0f),
                                      glm::vec3(glm::radians(90.0f), 0, 0),
                                      glm::vec3(2.0f, 0, 0));

    //位置变换
    glm::mat4 modelMat;
    glm::mat4 viewMat;
    glm::mat4 projMat;
    projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    //渲染循环
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        //清屏
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        viewMat = camera.GetViewMatrix();

        for (int i = 0; i < 10; i++) {
            //设置模型的位置
            modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);

            //设置材质的着色器
            myShader->use();
            //绑定材质
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, myMaterial->diffuse);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, myMaterial->specular);
            //设置材质的Uniform
            glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
            glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
            glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
            glUniform3f(glGetUniformLocation(myShader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
            glUniform3f(glGetUniformLocation(myShader->ID, "ambientColor"), 0.3f, 0.3f, 0.3f);
            glUniform3f(glGetUniformLocation(myShader->ID, "cameraPos"), camera.Position.x, camera.Position.y,
                        camera.Position.z);

            //定向光源
            glUniform3f(glGetUniformLocation(myShader->ID, "lightDirectional.pos"), lightD->position.x,
                        lightD->position.y,
                        lightD->position.z);
            glUniform3f(glGetUniformLocation(myShader->ID, "lightDirectional.color"), lightD->color.r,
                        lightD->color.g, lightD->color.b);
            glUniform3f(glGetUniformLocation(myShader->ID, "lightDirectional.dirToLight"), lightD->direction.x,
                        lightD->direction.y, lightD->direction.z);

            //点光源0
            glUniform3f(glGetUniformLocation(myShader->ID, "lightPoint0.pos"), lightP0->position.x,
                        lightP0->position.y,
                        lightP0->position.z);
            glUniform3f(glGetUniformLocation(myShader->ID, "lightPoint0.color"), lightP0->color.r,
                        lightP0->color.g, lightP0->color.b);
            glUniform3f(glGetUniformLocation(myShader->ID, "lightPoint0.dirToLight"), lightP0->direction.x,
                        lightP0->direction.y, lightP0->direction.z);

            //点光源1
            glUniform3f(glGetUniformLocation(myShader->ID, "lightPoint1.pos"), lightP1->position.x,
                        lightP1->position.y,
                        lightP1->position.z);
            glUniform3f(glGetUniformLocation(myShader->ID, "lightPoint1.color"), lightP1->color.r,
                        lightP1->color.g, lightP1->color.b);
            glUniform3f(glGetUniformLocation(myShader->ID, "lightPoint1.dirToLight"), lightP1->direction.x,
                        lightP1->direction.y, lightP1->direction.z);

            //点光源2
            glUniform3f(glGetUniformLocation(myShader->ID, "lightPoint2.pos"), lightP2->position.x,
                        lightP2->position.y,
                        lightP2->position.z);
            glUniform3f(glGetUniformLocation(myShader->ID, "lightPoint2.color"), lightP2->color.r,
                        lightP2->color.g, lightP2->color.b);
            glUniform3f(glGetUniformLocation(myShader->ID, "lightPoint2.dirToLight"), lightP2->direction.x,
                        lightP2->direction.y, lightP2->direction.z);

            //点光源3
            glUniform3f(glGetUniformLocation(myShader->ID, "lightPoint3.pos"), lightP3->position.x,
                        lightP3->position.y,
                        lightP3->position.z);
            glUniform3f(glGetUniformLocation(myShader->ID, "lightPoint3.color"), lightP3->color.r,
                        lightP3->color.g, lightP3->color.b);
            glUniform3f(glGetUniformLocation(myShader->ID, "lightPoint3.dirToLight"), lightP3->direction.x,
                        lightP3->direction.y, lightP3->direction.z);

            glUniform1f(glGetUniformLocation(myShader->ID, "constant"), PointLight::constant);
            glUniform1f(glGetUniformLocation(myShader->ID, "linear"), PointLight::linear);
            glUniform1f(glGetUniformLocation(myShader->ID, "quadratic"), PointLight::quadratic);

            //聚光源
            glUniform3f(glGetUniformLocation(myShader->ID, "lightSpot.pos"), lightS->position.x,
                        lightS->position.y,
                        lightS->position.z);
            glUniform3f(glGetUniformLocation(myShader->ID, "lightSpot.color"), lightS->color.r,
                        lightS->color.g, lightS->color.b);
            glUniform3f(glGetUniformLocation(myShader->ID, "lightSpot.dirToLight"), lightS->direction.x,
                        lightS->direction.y, lightS->direction.z);
            glUniform1f(glGetUniformLocation(myShader->ID, "lightSpot.cosInnerPhy"), lightS->cosInnerPhy);
            glUniform1f(glGetUniformLocation(myShader->ID, "lightSpot.cosOuterPhy"), lightS->cosOuterPhy);

            //设置材质球
            myMaterial->setUniform3f("material.ambient", myMaterial->ambient);
            myMaterial->setUniform1i("material.diffuse", myMaterial->Diffuse);
            myMaterial->setUniform1i("material.specular", myMaterial->Specular);
            myMaterial->setUniform1f("material.shininess", myMaterial->shininess);

            //画
            model->Draw(myMaterial);
        }

        //刷新缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
        camera.UpdateCameraPosition();
    }

    //退出
    printf("Exit Application");
    glfwTerminate();
    return 0;
}

//进程输入
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.speedZ = 0.1f;
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.speedZ = -0.1f;
    } else {
        camera.speedZ = 0;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.speedX = 0.1f;
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.speedX = -0.1f;
    } else {
        camera.speedX = 0;
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.speedY = 0.1f;
    } else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.speedY = -0.1f;
    } else {
        camera.speedY = 0;
    }
}

//鼠标输入
void mouse_callback(GLFWwindow *window, double xPos, double yPos) {
    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;

        firstMouse = false;
    }

    float deltaX, deltaY;
    deltaX = xPos - lastX;
    deltaY = yPos - lastY;

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(deltaX, deltaY);
}

//加载图像到GPU
unsigned int LoadImageToGPU(const char *filename, GLint internalFormat, GLenum format, int textureSlot) {
    unsigned int texBuffer;
    glGenTextures(1, &texBuffer);
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, texBuffer);

    int width, height, nrChannel;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannel, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("load image failed.");
    }
    stbi_image_free(data);

    return texBuffer;
}