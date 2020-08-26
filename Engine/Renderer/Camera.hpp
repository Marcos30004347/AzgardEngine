#ifndef CAMERA_RENDERER_H
#define CAMERA_RENDERER_H

#include "DataStructures/Identifier.hpp"

enum CameraProjection {
    PERSPECTIVE_PROJECTION,
    ORTHOGONAL_PROJECTION,
};

struct CameraHandle {
    Identifier id;
};


#endif