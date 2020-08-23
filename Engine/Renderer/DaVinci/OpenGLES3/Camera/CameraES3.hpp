#ifndef CAMERAES3_H
#define CAMERAES3_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
// #include "glm/gtx/rotate_vector.hpp"

enum ProjectionType {
    OrthogonalProjection,
    PerspectiveProjection,
};

class CameraES3 {
    private:
    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;

    glm::vec3 Forward;
    glm::vec3 Up;

    glm::vec3 Position;

    ProjectionType type;

    public:

    CameraES3();
    ~CameraES3();
    CameraES3(glm::vec3 position, glm::vec3 forward);

    void SetProjectionOrthogonal(float left, float right, float bottom, float up, float near, float far);
    void SetProjectionPerspective(float fov, float aspect, float near, float far);

    glm::mat4 GetView();
    glm::mat4 GetProjection();

    void Destroy();

    void Translate(glm::vec3 to);
    void LookAt(glm::vec3 direction);
    void Rotate(float angle, glm::vec3 axis);

};

#endif