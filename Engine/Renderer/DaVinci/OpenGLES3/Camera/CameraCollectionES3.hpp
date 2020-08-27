#include "definitions.hpp"

#ifndef CAMERAHCOLLECTIONES3_H
#define CAMERAHCOLLECTIONES3_H

#ifdef OPENGLES3_API

#include "DataStructures/Collection.hpp"

#include "CameraES3.hpp"

#include<mutex>

#define CAMERABATCHSIZE 64


struct CameraBatchES3 {
    CameraES3 mesh[CAMERABATCHSIZE];
    CameraBatchES3() {}
};


class CameraCollectionES3 : public Collection<CameraES3> {
    private:
    CameraCollectionES3();
    ~CameraCollectionES3();

    std::vector<CameraBatchES3> CameraPatch;
    static std::mutex mutex;

    public:

    static void StartUp();
    static void ShutDown();

    Identifier Insert(CameraES3& cam);
    void Delete(Identifier id);
    CameraES3& Get(Identifier id);
};


#endif
#endif