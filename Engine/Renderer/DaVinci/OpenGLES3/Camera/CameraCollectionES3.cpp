#include "definitions.hpp"

#ifdef OPENGLES3_API

#include "CameraCollectionES3.hpp"

std::mutex CameraCollectionES3::mutex;

template<> CameraCollectionES3* Singleton<CameraCollectionES3>::instance = nullptr;

CameraCollectionES3::CameraCollectionES3() {
    this->CameraPatch = std::vector<CameraBatchES3>();
    this->CameraPatch.push_back(CameraBatchES3());
}

CameraCollectionES3::~CameraCollectionES3() {}

void CameraCollectionES3::StartUp() {
    CameraCollectionES3::instance = new CameraCollectionES3();
}

void CameraCollectionES3::ShutDown() {
    delete CameraCollectionES3::instance;
}

Identifier CameraCollectionES3::Insert(CameraES3& cam) {
    mutex.lock();
    Identifier id;

    if(this->avaliableIds.GetAvaliable(&id)) {
        unsigned short minnor = GetIdentifierMinnor(id);
        unsigned short major = GetIdentifierMajor(id);
    
    
        this->CameraPatch[minnor].mesh[major] = cam;
        mutex.unlock();
        return id;
    }

    this->CameraPatch[this->CameraPatch.size() - 1].mesh[this->lastGroupAvaliable] = cam;

    id = EncriptId(this->CameraPatch.size() - 1, this->lastGroupAvaliable);
    
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);


    this->lastGroupAvaliable++;

    if(CAMERABATCHSIZE <= this->lastGroupAvaliable) {
        CameraBatchES3 smb;
        CameraPatch.push_back(smb);
    
        this->lastGroupAvaliable = 0;
    }

    mutex.unlock();
    return id;
}

void CameraCollectionES3::Delete(Identifier id) {
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);

    CameraPatch[minnor].mesh[major].Destroy();

    this->avaliableIds.MakeAvaliable(id);
};

CameraES3& CameraCollectionES3::Get(Identifier id) {
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);

    return CameraPatch[minnor].mesh[major];
}



#endif