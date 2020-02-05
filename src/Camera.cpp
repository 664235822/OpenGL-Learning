//
// Created by 朱洲 on 2020/2/5.
//

#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp) {
    Position = position;
    WorldUp = worldUp;
    Forward = glm::normalize(target - position);
    Right = glm::normalize(glm::cross(Forward, WorldUp));
    Up = glm::normalize(glm::cross(Forward, Right));
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp) {
    Position = position;
    WorldUp = worldUp;
    Pitch = pitch;
    Yaw = yaw;
    Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
    Forward.y = glm::sin(Pitch);
    Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
    Right = glm::normalize(glm::cross(Forward, WorldUp));
    Up = glm::normalize(glm::cross(Forward, Right));
}


glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(Position, Position + Forward, WorldUp);
}

void Camera::UpdateCameraVectors() {
    Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
    Forward.y = glm::sin(Pitch);
    Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
    Right = glm::normalize(glm::cross(Forward, WorldUp));
    Up = glm::normalize(glm::cross(Forward, Right));
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY) {
    Pitch += deltaY * senseY;
    Yaw -= deltaX * senseX;
    UpdateCameraVectors();
}

void Camera::UpdateCameraPosition() {
    Position += Forward * speedZ;
}

