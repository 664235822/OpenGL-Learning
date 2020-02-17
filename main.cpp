#include <glew.h>
#include <glfw3.h>
#include <cmath>
#include "src/Shader.h"
#include "src/Camera.h"
#include "src/Material.h"

#define STB_IMAGE_IMPLEMENTATION

#include "src/stb_image.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f
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

    //创建VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //创建VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //创建着色器
    Shader *myShader = new Shader("../shader/vertexShader.vert", "../shader/fragmentShader.frag");
    //创建材质球
    Material *myMaterial = new Material(myShader,
                                        glm::vec3(1.0f, 1.0f, 1.0f),
                                        glm::vec3(1.0f, 1.0f, 1.0f),
                                        glm::vec3(1.0f, 1.0f, 1.0f),
                                        32.0f);

    //顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    //颜色属性
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    //glEnableVertexAttribArray(1);
    //uv属性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    //法向量属性
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (5 * sizeof(float)));
    glEnableVertexAttribArray(3);

    //应用纹理
    unsigned int texBuffer;
    texBuffer = LoadImageToGPU("../img/wood.jpeg", GL_RGB, GL_RGB, 0);

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
            //设置材质的纹理
            glBindTexture(GL_TEXTURE_2D, texBuffer);
            //设置材质的Uniform
            glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);
            glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
            glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
            glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
            glUniform3f(glGetUniformLocation(myShader->ID, "objColor"), 1.0f, 0.5f, 0.31f);
            glUniform3f(glGetUniformLocation(myShader->ID, "ambientColor"), 0.5f, 0.5f, 0.5f);
            glUniform3f(glGetUniformLocation(myShader->ID, "lightPos"), 10.0f, 10.0f, 5.0f);
            glUniform3f(glGetUniformLocation(myShader->ID, "lightColor"), 1.0f, 1.0f, 1.0f);
            glUniform3f(glGetUniformLocation(myShader->ID, "cameraPos"), camera.Position.x, camera.Position.y,
                        camera.Position.z);
            //设置材质球
            myMaterial->use();
            //设置模型
            glBindVertexArray(VAO);

            //画
            glDrawArrays(GL_TRIANGLES, 0, 36);
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