#include "definitions.hpp"
#ifdef OPENGLES3_SUPORTED

#include "MeshManagerES3.hpp"
#include<string.h>

std::mutex MeshManagerES3::mutex;

IdentifierQueue MeshManagerES3::avaliableIds;

Identifier MeshManagerES3::lastGroupAvaliable = 0;

MeshES3* MeshManagerES3::data = nullptr;

unsigned int MeshManagerES3::maxMeshesCount = 0;

MeshManagerES3::MeshManagerES3() {}

MeshManagerES3::~MeshManagerES3() {}

void MeshManagerES3::StartUp(unsigned int maxMeshesCount) {
    MeshManagerES3::avaliableIds = IdentifierQueue();
    MeshManagerES3::lastGroupAvaliable = 0;

    MeshManagerES3::instance = new MeshManagerES3();

    MeshManagerES3::maxMeshesCount = maxMeshesCount;
    MeshManagerES3::data = (MeshES3*)malloc(sizeof(MeshES3)*maxMeshesCount);
}

void MeshManagerES3::ShutDown() {
    MeshManagerES3::maxMeshesCount = 0;
    MeshManagerES3::lastGroupAvaliable = 0;

    free(MeshManagerES3::instance);
    free(MeshManagerES3::data);
}

Identifier MeshManagerES3::Insert(MeshES3& model) {
    mutex.lock();
    Identifier id;
    
    if(avaliableIds.GetAvaliable(&id)) {
        MeshManagerES3::data[id] = model;
    } else {
        MeshManagerES3::data[MeshManagerES3::lastGroupAvaliable] = model;
        id = MeshManagerES3::lastGroupAvaliable;
        MeshManagerES3::lastGroupAvaliable++;

        if(MeshManagerES3::lastGroupAvaliable >= MeshManagerES3::maxMeshesCount) {
            MeshES3* tmp = MeshManagerES3::data;
            MeshManagerES3::data = (MeshES3*)malloc(sizeof(MeshES3)*(MeshManagerES3::maxMeshesCount + 500));
            memcpy(MeshManagerES3::data, tmp, sizeof(MeshES3)*MeshManagerES3::maxMeshesCount);
            MeshManagerES3::maxMeshesCount = MeshManagerES3::maxMeshesCount + 500;
        }
    }

    mutex.unlock(); 
    return id;
}

void MeshManagerES3::Delete(Identifier id) {
    MeshManagerES3::data[id].DestroyBuffers();
    avaliableIds.MakeAvaliable(id);
};

MeshES3& MeshManagerES3::Get(Identifier id) {
    return MeshManagerES3::data[id];
}



#endif