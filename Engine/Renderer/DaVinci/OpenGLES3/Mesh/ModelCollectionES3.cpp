#include "definitions.hpp"
#ifdef OPENGLES3_API

#include "ModelCollectionES3.hpp"


std::mutex ModelCollectionES3::mutex;


ModelCollectionES3::ModelCollectionES3() {
    this->avaliableModeleIds = IdentifierQueue();
    this->lastAvaliableBatch = 0;
    this->modelPatch = std::vector<ModelBatchES3>(1);
}

void ModelCollectionES3::Destroy() {}

ModelCollectionES3::~ModelCollectionES3() {}


Identifier ModelCollectionES3::Allocate(ModelData ModelData) {
    mutex.lock();
    Identifier id;
    
    if(avaliableModeleIds.GetAvaliable(&id)) {
        unsigned short minnor = GetIdentifierMinnor(id);
        unsigned short major = GetIdentifierMajor(id);
    
    
        this->modelPatch[minnor].model[major] = ModelES3(ModelData);
        mutex.unlock();

        return id;
    }

    this->modelPatch[this->modelPatch.size() - 1].model[lastAvaliableBatch] = ModelES3(ModelData);

    id = EncriptId(this->modelPatch.size() - 1, lastAvaliableBatch);
    
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);


    lastAvaliableBatch++;

    if(MODELBATCHSIZE <= lastAvaliableBatch) {
        ModelBatchES3 smb;
        modelPatch.push_back(smb);
    
        lastAvaliableBatch = 0;
    }

    mutex.unlock();
    return id;
}

void ModelCollectionES3::Dellocate(Identifier id) {
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);


    modelPatch[minnor].model[major].Destroy();

    avaliableModeleIds.MakeAvaliable(id);
};

ModelES3& ModelCollectionES3::Get(Identifier id) {
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);
    return modelPatch[minnor].model[major];
}



#endif