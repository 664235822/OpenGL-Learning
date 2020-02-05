//
// Created by 朱洲 on 2020/2/5.
//

#ifndef OPENGL_LEARNING_CAMERA_H
#define OPENGL_LEARNING_CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera {

public:
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp);

    Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp);

    glm::vec3 Position;
    glm::vec3 Forward;
    glm::vec3 Right;
    glm::vec3 Up;
    glm::vec3 WorldUp;

    float Pitch;
    float Yaw;

    float senseX = 0.01f;
    float senseY = 0.01f;

    float speedZ = 0;

    glm::mat4 GetViewMatrix();

    void ProcessMouseMovement(float deltaX, float deltaY);

    void UpdateCameraPosition();

private:

    void UpdateCameraVectors();
};


#endif //OPENGL_LEARNING_CAMERA_H
