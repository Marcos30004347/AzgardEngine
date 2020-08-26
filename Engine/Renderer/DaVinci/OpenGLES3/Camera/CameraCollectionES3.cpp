#include "definitions.hpp"
#ifdef OPENGLES3_API

#include "CameraCollectionES3.hpp"


std::mutex CameraCollectionES3::mutex;


CameraCollectionES3::CameraCollectionES3() {
    this->avaliableCameraeIds = IdentifierQueue();
    this->LastAvaliableBatch = 0;
    this->CameraPatch = std::vector<CameraBatchES3>();
    this->CameraPatch.push_back(CameraBatchES3());
}

CameraCollectionES3::~CameraCollectionES3() { this->Destroy(); }

void CameraCollectionES3::Destroy() {}

Identifier CameraCollectionES3::Allocate(glm::vec3 position, glm::vec3 forward, CameraProjection projection) {
    mutex.lock();
    Identifier id;

    if(avaliableCameraeIds.GetAvaliable(&id)) {
        unsigned short minnor = GetIdentifierMinnor(id);
        unsigned short major = GetIdentifierMajor(id);
    
    
        this->CameraPatch[minnor].mesh[major] = CameraES3(position, forward, projection);
        mutex.unlock();
        return id;
    }

    this->CameraPatch[this->CameraPatch.size() - 1].mesh[LastAvaliableBatch] = CameraES3(position, forward, projection);

    id = EncriptId(this->CameraPatch.size() - 1, LastAvaliableBatch);
    
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);


    LastAvaliableBatch++;

    if(CAMERABATCHSIZE <= LastAvaliableBatch) {
        CameraBatchES3 smb;
        CameraPatch.push_back(smb);
    
        LastAvaliableBatch = 0;
    }

    mutex.unlock();
    return id;
}

void CameraCollectionES3::Dellocate(Identifier id) {
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);


    CameraPatch[minnor].mesh[major].Destroy();

    avaliableCameraeIds.MakeAvaliable(id);
};

CameraES3& CameraCollectionES3::Get(Identifier id) {
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);

    return CameraPatch[minnor].mesh[major];
}



#endif