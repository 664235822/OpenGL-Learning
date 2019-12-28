#include <glew.h>
#include <glfw3.h>
#include <iostream>

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

    //渲染循环
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //退出
    printf("Exit Application");
    glfwTerminate();
    return 0;
}