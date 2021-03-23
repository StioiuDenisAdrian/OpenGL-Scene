#include "Camera.hpp"


namespace gps {

    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget)
    {
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraDirection = glm::normalize(cameraTarget - cameraPosition);
        this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        this->cameraRightDirection = glm::normalize(glm::cross(this->cameraDirection, this->cameraUp));
    }

    glm::mat4 Camera::getViewMatrix()
    {
        return glm::lookAt(cameraPosition, cameraPosition + cameraDirection, cameraUp);
    }

    glm::vec3 Camera::getCameraTarget()
    {
        return cameraTarget;
    }

    glm::vec3 Camera::getCameraPosition() {
        return cameraPosition;
    }

    void Camera::move(MOVE_DIRECTION direction, float speed)
    {
        switch (direction) {
        case MOVE_FORWARD:
            cameraPosition += cameraDirection * speed;
            break;

        case MOVE_BACKWARD:
            cameraPosition -= cameraDirection * speed;
            break;

        case MOVE_RIGHT:
            cameraPosition += cameraRightDirection * speed;
            break;

        case MOVE_LEFT:
            cameraPosition -= cameraRightDirection * speed;
            break;
        }
    }

    void Camera::rotate(float pitch, float yaw)
    {
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraDirection = glm::normalize(front);
        cameraRightDirection = glm::normalize(glm::cross(cameraDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
        cameraUp = glm::normalize(glm::cross(cameraRightDirection, cameraDirection));
    }

}
