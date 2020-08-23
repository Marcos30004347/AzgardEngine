#include "definitions.hpp"

#ifndef CAMERAHCOLLECTIONES3_H
#ifdef OPENGLES3_API

#define CAMERAHCOLLECTIONES3_H

#include "DataStructures/Identifier.hpp"
#include "CameraES3.hpp"

#include<mutex>

#define CAMERABATCHSIZE 64


struct CameraBatchES3 {
    CameraES3 mesh[CAMERABATCHSIZE];
    CameraBatchES3() {}
};


class CameraCollectionES3 {
    private:

    unsigned short LastAvaliableBatch;

    IdentifierQueue avaliableCameraeIds;

    std::vector<CameraBatchES3> CameraPatch;

    static std::mutex mutex;

    public:
    CameraCollectionES3();
    ~CameraCollectionES3();

    Identifier Allocate(glm::vec3 position, glm::vec3 forward);
    void Dellocate(Identifier id);
    CameraES3 Get(Identifier id);

    void Destroy();
};




#endif
#endif