#include "definitions.hpp"
#ifdef OPENGLES3_API

#include "ModelCollectionES3.hpp"


std::mutex ModelCollectionES3::mutex;
template<> ModelCollectionES3* Singleton<ModelCollectionES3>::instance = nullptr;


ModelCollectionES3::ModelCollectionES3() {
    this->avaliableIds = IdentifierQueue();
    this->modelPatch = std::vector<ModelBatchES3>(1);
}

void ModelCollectionES3::Destroy() {}

ModelCollectionES3::~ModelCollectionES3() {}

void ModelCollectionES3::StartUp() {
    ModelCollectionES3::instance = new ModelCollectionES3();
}

void ModelCollectionES3::ShutDown() {
    delete ModelCollectionES3::instance;
}

Identifier ModelCollectionES3::Insert(ModelES3& model) {
    mutex.lock();
    Identifier id;
    
    if(avaliableIds.GetAvaliable(&id)) {
        unsigned short minnor = GetIdentifierMinnor(id);
        unsigned short major = GetIdentifierMajor(id);
    
    
        this->modelPatch[minnor].model[major] = model;
        mutex.unlock();

        return id;
    }

    this->modelPatch[this->modelPatch.size() - 1].model[this->lastGroupAvaliable] = model;

    id = EncriptId(this->modelPatch.size() - 1, this->lastGroupAvaliable);
    
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);


    this->lastGroupAvaliable++;

    if(MODELBATCHSIZE <= this->lastGroupAvaliable) {
        ModelBatchES3 smb;
        modelPatch.push_back(smb);
    
        this->lastGroupAvaliable = 0;
    }

    mutex.unlock();
    return id;
}

void ModelCollectionES3::Delete(Identifier id) {
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);


    modelPatch[minnor].model[major].Destroy();

    avaliableIds.MakeAvaliable(id);
};

ModelES3& ModelCollectionES3::Get(Identifier id) {
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);
    return modelPatch[minnor].model[major];
}



#endif