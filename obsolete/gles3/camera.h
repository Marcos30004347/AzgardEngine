#ifndef GLES3_CAMERA_H
#define GLES3_CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
// #include "glm/gtx/rotate_vector.hpp"

enum projection_type {
    ORTHOGONAL,
    PERSPECTIVE,
};

class GLES3_Camera {
    private:
    glm::mat4 _view;
    glm::mat4 _projection;

    glm::vec3 _forward;
    glm::vec3 _up;

    glm::vec3 _position;

    public:

    GLES3_Camera(projection_type type, glm::vec3 position, glm::vec3 forward, float aspect, float fov) {
        this->_up = glm::vec3(0.0f,1.0f,0.0f);

        this->_forward = forward;

        this->_position = position;

        this->_view = glm::lookAt(this->_position, this->_position + this->_forward, this->_up);
        if(type == PERSPECTIVE) {
            this->_projection = glm::perspective(fov, aspect, 0.1f, 1000.0f);
        } else if(type == ORTHOGONAL) {
            this->_projection = glm::ortho(-1.0f,3.0f,-2.0f,2.0f,-10.0f, 1000.0f);
        }
    }

    glm::mat4 getView() {

        return this->_view;
    }

    glm::mat4 getProjection() {

        return this->_projection;
    }

    void translate(glm::vec3 to) { 
        this->_position+=to;
        this->_view = glm::lookAt(this->_position, this->_position + this->_forward, this->_up);
    }

    void look_at(glm::vec3 direction) {
        this->_view = glm::lookAt(this->_position, this->_position + this->_forward, this->_up);
    }

    void rotate(float angle, glm::vec3 axis) { 
        this->_view = glm::rotate(this->_view, glm::radians(angle), axis);
    }

};

#endif