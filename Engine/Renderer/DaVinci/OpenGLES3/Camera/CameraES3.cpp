#include "definitions.hpp"

#ifdef OPENGLES3_API
#include "CameraES3.hpp"

CameraES3::CameraES3() {}
CameraES3::~CameraES3() { this->Destroy(); }

CameraES3::CameraES3(glm::vec3 position, glm::vec3 forward) {
    this->Up = glm::vec3(0.0f,1.0f,0.0f);
    this->Forward = forward;
    this->Position = position;
    this->ViewMatrix = glm::lookAt(this->Position, this->Position + this->Forward, this->Up);
}

void CameraES3::SetProjectionOrthogonal(float left, float right, float bottom, float up, float near, float far) {
        this->ProjectionMatrix = glm::ortho(left, right, bottom, up, near, far);
        this->type = OrthogonalProjection;
}

void CameraES3::Destroy() {}

void CameraES3::SetProjectionPerspective(float fov, float aspect, float near, float far) {
    this->ProjectionMatrix = glm::perspective(fov, aspect, near, far);
    this->type = PerspectiveProjection;
}

glm::mat4 CameraES3::GetView() {
    return this->ViewMatrix;
}

glm::mat4 CameraES3::GetProjection() {
    return this->ProjectionMatrix;
}

void CameraES3::Translate(glm::vec3 to) { 
    this->Position+=to;
    this->ViewMatrix = glm::lookAt(this->Position, this->Position + this->Forward, this->Up);
}

void CameraES3::LookAt(glm::vec3 direction) {
    this->ViewMatrix = glm::lookAt(this->Position, this->Position + this->Forward, this->Up);
}

void CameraES3::Rotate(float angle, glm::vec3 axis) { 
    this->ViewMatrix = glm::rotate(this->ViewMatrix, glm::radians(angle), axis);
}

#endif