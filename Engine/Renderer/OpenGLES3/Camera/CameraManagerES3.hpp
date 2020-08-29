#include "definitions.hpp"

#ifndef CAMERAHCOLLECTIONES3_H
#define CAMERAHCOLLECTIONES3_H

#ifdef OPENGLES3_SUPORTED

#include "DataStructures/Identifier.hpp"
#include "DataStructures/Singleton.hpp"

#include "CameraES3.hpp"

#include<mutex>

class CameraManagerES3 : public Singleton<CameraManagerES3> {
    private:
    CameraManagerES3();
    ~CameraManagerES3();

    static IdentifierQueue avaliableIds;
    static unsigned int lastGroupAvaliable;
    static unsigned int maxCamerasCount;
    static CameraES3* data;
    static std::mutex mutex;

    public:

    static void StartUp(unsigned int maxCamerasCount = 200000);
    static void ShutDown();

    Identifier Insert(CameraES3& cam);
    void Delete(Identifier id);
    CameraES3& Get(Identifier id);
};


#endif
#endif