#include "definitions.hpp"
#ifdef OPENGLES3_API

#include "ShaderCollectionES3.hpp"


std::mutex ShaderCollectionES3::mutex;


ShaderCollectionES3::ShaderCollectionES3() {
    this->ShaderPatch = std::vector<ShaderBatchES3>();
    this->ShaderPatch.push_back(ShaderBatchES3());
}

ShaderCollectionES3::~ShaderCollectionES3() { this->Destroy(); }

void ShaderCollectionES3::Destroy() {}

void ShaderCollectionES3::StartUp() {
    ShaderCollectionES3::instance = new ShaderCollectionES3();
}
void ShaderCollectionES3::ShutDown() {
    delete ShaderCollectionES3::instance;
}

Identifier ShaderCollectionES3::Insert(ShaderES3& shader) {
    mutex.lock();
    Identifier id;

    if(avaliableIds.GetAvaliable(&id)) {
        unsigned short minnor = GetIdentifierMinnor(id);
        unsigned short major = GetIdentifierMajor(id);
    
    
        this->ShaderPatch[minnor].mesh[major] = shader;
        mutex.unlock();
        return id;
    }

    this->ShaderPatch[this->ShaderPatch.size() - 1].mesh[this->lastGroupAvaliable] = shader;

    id = EncriptId(this->ShaderPatch.size() - 1, this->lastGroupAvaliable);
    
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);


    this->lastGroupAvaliable++;

    if(SHADERBATCHSIZE <= this->lastGroupAvaliable) {
        ShaderBatchES3 smb;
        ShaderPatch.push_back(smb);
    
        this->lastGroupAvaliable = 0;
    }

    mutex.unlock();
    return id;
}

void ShaderCollectionES3::Delete(Identifier id) {
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);


    ShaderPatch[minnor].mesh[major].Destroy();

    avaliableIds.MakeAvaliable(id);
};

ShaderES3& ShaderCollectionES3::Get(Identifier id) {
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);
    return ShaderPatch[minnor].mesh[major];
}



#endif