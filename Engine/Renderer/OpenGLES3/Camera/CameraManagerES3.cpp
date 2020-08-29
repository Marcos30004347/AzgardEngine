#include "definitions.hpp"

#ifdef OPENGLES3_SUPORTED

#include "CameraManagerES3.hpp"
#include <string.h>

std::mutex CameraManagerES3::mutex;

IdentifierQueue CameraManagerES3::avaliableIds;

Identifier CameraManagerES3::lastGroupAvaliable = 0;

CameraES3* CameraManagerES3::data = nullptr;

unsigned int CameraManagerES3::maxCamerasCount = 0;

CameraManagerES3::CameraManagerES3() {}

CameraManagerES3::~CameraManagerES3() {}

void CameraManagerES3::StartUp(unsigned int maxCamerasCount) {
    CameraManagerES3::avaliableIds = IdentifierQueue();
    CameraManagerES3::lastGroupAvaliable = 0;

    CameraManagerES3::instance = new CameraManagerES3();

    CameraManagerES3::maxCamerasCount = maxCamerasCount;
    CameraManagerES3::data = (CameraES3*)malloc(sizeof(CameraES3)*maxCamerasCount);
}

void CameraManagerES3::ShutDown() {
    CameraManagerES3::lastGroupAvaliable = 0;
    CameraManagerES3::maxCamerasCount = 0;

    free(CameraManagerES3::data);
    free(CameraManagerES3::instance);
}

Identifier CameraManagerES3::Insert(CameraES3& cam) {
    mutex.lock();
    Identifier id;

    if(this->avaliableIds.GetAvaliable(&id)) {
        CameraManagerES3::data[id] = cam;
    } else {
        CameraManagerES3::data[CameraManagerES3::lastGroupAvaliable] = cam;

        id = CameraManagerES3::lastGroupAvaliable;
        CameraManagerES3::lastGroupAvaliable++;
        if(CameraManagerES3::lastGroupAvaliable >= CameraManagerES3::maxCamerasCount) {
            CameraES3* tmp = CameraManagerES3::data;
            CameraManagerES3::data = (CameraES3*)malloc(sizeof(CameraES3)*(CameraManagerES3::maxCamerasCount + 500));
            memcpy(CameraManagerES3::data, tmp, sizeof(CameraES3)*CameraManagerES3::maxCamerasCount);
            CameraManagerES3::maxCamerasCount = CameraManagerES3::maxCamerasCount + 500;
        }
    }

    mutex.unlock();
    return id;
}

void CameraManagerES3::Delete(Identifier id) {
    CameraManagerES3::data[id].Destroy();
    this->avaliableIds.MakeAvaliable(id);
};

CameraES3& CameraManagerES3::Get(Identifier id) {
    return CameraManagerES3::data[id];
}



#endif