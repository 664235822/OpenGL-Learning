cmake_minimum_required(VERSION 3.15)
project(OpenGL_Learning)

set(CMAKE_CXX_STANDARD 14)

set(GLEW_H /usr/local/Cellar/glew/2.1.0_1/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.3.2/include/GLFW)
set(ASSIMP_H /usr/local/Cellar/assimp/5.0.1/include)
set(GLAD_H /usr/local/include/glad)
set(KH_H /usr/local/include/KHR)
set(GLM_H /usr/local/include/glm/glm)
include_directories(${GLEW_H} ${GLFW_H} ${ASSIMP_H} ${GLAD_H} ${KH_H} ${GLM_H} )

# 添加目标链接
set(GLEW_LINK /usr/local/Cellar/glew/2.1.0_1/lib/libGLEW.2.1.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.2/lib/libglfw.3.dylib)
set(ASSIMP_LINK /usr/local/Cellar/assimp/5.0.1/lib/libassimp.5.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK} ${ASSIMP_LINK})

# 执行编译命令
# 这个glad.c在第2步中说过要拉到项目中，注意路径
set(SOURCE_FILES "src/glad.c" "main.cpp" src/Shader.cpp src/Shader.h src/stb_image.h src/Camera.cpp src/Camera.h src/Material.cpp src/Material.h src/DirectionLight.cpp src/DirectionLight.h src/PointLight.cpp src/PointLight.h src/SpotLight.cpp src/SpotLight.h src/Mesh.cpp src/Mesh.h src/Model.cpp src/Model.h)
add_executable(OpenGL_Learning ${SOURCE_FILES})

# mac下这步很重要
if (APPLE)
    target_link_libraries(OpenGL_Learning "-framework OpenGL")
    target_link_libraries(OpenGL_Learning "-framework GLUT")
endif()