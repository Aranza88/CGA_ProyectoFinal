#include "Headers/ThirdPersonCamera.h"

ThirdPersonCamera::ThirdPersonCamera(){
    pitch = glm::radians(20.0f);
    yaw = 0.0f;
    angleAroundTarget = 0.0f;
    angleTarget = 0.0;
    distanceFromTarget = 1.0f;
    sensitivity = SENSITIVTY;
    worldUp = glm::vec3(0.0, 1.0, 0.0);
    updateCamera();
}

void ThirdPersonCamera::mouseMoveCamera(float xoffset, float yoffset, float dt){
    // Camera controls
    float cameraSpeed = sensitivity * dt;

    // Calculate pitch
    pitch += yoffset * cameraSpeed;
    // Calculate Angle Arround
    angleAroundTarget -= xoffset * cameraSpeed;
    if(pitch > M_PI / 2)
        pitch = M_PI / 2 - 0.01;
    if(pitch < -M_PI / 2)
        pitch = -M_PI / 2 + 0.01;
    updateCamera();
}

void ThirdPersonCamera::scrollMoveCamera(float soffset, float dt){
    // Camera controls
    float cameraSpeed = sensitivity * dt;
    // Calculate zoom
    float zoomLevel = soffset * cameraSpeed;
    distanceFromTarget -= zoomLevel;
    updateCamera();
}

void ThirdPersonCamera::updateCamera(){
    //Calculate Horizontal distance
    float horizontalDistance = distanceFromTarget * cos(pitch);
    //Calculate Vertical distance
    float verticalDistance = distanceFromTarget * sin(pitch);

    //Calculate camera position
    float theta = angleTarget + angleAroundTarget;
    float offsetx = horizontalDistance * sin(theta);
    float offsetz = horizontalDistance * cos(theta);

    float x = cameraTarget.x - offsetx;
    float y = cameraTarget.y + verticalDistance;
    float z = cameraTarget.z - offsetz;
    if (x > -83 && x < 22)
        position.x = x;
    if (z > -6.2 && z < 39.2)
        position.z = z;
    if (y > 1 && y < 10)
        position.y = y;

    yaw = angleTarget - (180 + angleAroundTarget);

    if (distanceFromTarget < 0)
    	front = glm::normalize(position - cameraTarget);
    else
    	front = glm::normalize(cameraTarget - position);

    this->right = glm::normalize(glm::cross(this->front, this->worldUp));
    this->up = glm::normalize(glm::cross(this->right, this->front));
}
