#ifndef CAMERAES3_H
#define CAMERAES3_H

#include "Renderer/Camera.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"


class CameraES3 {
    private:
    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;

    glm::vec3 Forward;
    glm::vec3 Up;

    glm::vec3 Position;

    CameraProjection projection;

    public:

    CameraES3();
    ~CameraES3();
    CameraES3(glm::vec3 position, glm::vec3 forward, CameraProjection projection);

    void SetProjectionOrthogonal(float left = -1.f, float right = 1.f, float bottom = -1.f, float up = 1.f, float near = 0.1f , float far = 1000.f);
    void SetProjectionPerspective(float fov = glm::radians(90.f), float aspect = 1200.f/720, float near = 0.1f, float far = 1000.f);

    glm::mat4& GetView();
    glm::mat4& GetProjection();
    
    glm::vec3 GetForward();
    glm::vec3 GetPosition();

    void Destroy();

    void Translate(glm::vec3 to);
    void LookAt(glm::vec3 direction);
    void Rotate(float angle, glm::vec3 axis);
};

#endif