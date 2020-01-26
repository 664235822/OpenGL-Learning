#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "math.h"

float vertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 0, 0,
        0.5f, -0.5f, 0.0f, 0, 1.0f, 0,
        -0.5f, -0.5f, 0.0f, 0, 0, 1.0f,
        -0.5f, 0.5f, 0.0f, 0.3f, 0.5f, 0.7f
};

unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
};


const char *vertexShaderSource = "#version 330 core \n"
                                 "layout (location = 0) in vec3 aPos; \n"
                                 "layout (location = 1) in vec3 aColor; \n"
                                 "out vec4 vertexColor;\n"
                                 "void main(){\n"
                                 "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);\n"
                                 "}";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "in vec4 vertexColor;\n"
                                   "uniform vec4 ourColor;\n"
                                   "out vec4 FragColor;\n"
                                   "void main(){\n"
                                   "FragColor = vertexColor;}";

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

    //编译vertexShader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //编译fragmentShader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //创建shader程序
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    //颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //渲染循环
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //画三角形、矩形
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        //使用着色器
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        glUseProgram(shaderProgram);
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