#include <glew.h>
#include <glfw3.h>
#include <cmath>
#include "src/Shader.h"

#define STB_IMAGE_IMPLEMENTATION

#include "src/stb_image.h"

float vertices[] = {
        //位置3,颜色3,纹理2
        0.5f, 0.5f, 0.0f, 1.0f, 0, 0, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 0, 1.0f, 0, 1.0f, 0,
        -0.5f, -0.5f, 0.0f, 0, 0, 1.0f, 0, 0,
        -0.5f, 0.5f, 0.0f, 0.3f, 0.5f, 0.7f, 0, 1.0f
};

unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
};

void processInput(GLFWwindow *window);

int main(void) {
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

    //背面剔除
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    //创建VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //创建VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //创建EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //创建着色器
    Shader *myShader = new Shader("../shader/vertexShader.txt", "../shader/fragmentShader.txt");

    //顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    //颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //uv属性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //应用纹理
    unsigned int texBuffer;
    glGenTextures(1, &texBuffer);
    glBindTexture(GL_TEXTURE_2D, texBuffer);

    int width, height, nrChannel;
    unsigned char *data = stbi_load("../img/wood.jpeg", &width, &height, &nrChannel, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("load image failed.");
    }
    stbi_image_free(data);

    //渲染循环
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //画矩形
        glBindTexture(GL_TEXTURE_2D, texBuffer);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        //使用着色器
        myShader->use();

        //glDrawArrays(GL_TRIANGLES,0,3);//三角形
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//矩形

        glfwSwapBuffers(window);
        glfwPollEvents();
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
}