#include "definitions.hpp"
#ifdef OPENGLES3_API

#include "MaterialCollectionES3.hpp"


std::mutex MaterialCollectionES3::mutex;


MaterialCollectionES3::MaterialCollectionES3() {
    this->avaliableMaterialeIds = IdentifierQueue();
    this->LastAvaliableBatch = 0;
    this->MaterialPatch = std::vector<MaterialBatchES3>();
    this->MaterialPatch.push_back(MaterialBatchES3());
}

MaterialCollectionES3::~MaterialCollectionES3() { this->Destroy(); }

void MaterialCollectionES3::Destroy() {}

Identifier MaterialCollectionES3::Allocate() {
    mutex.lock();
    Identifier id;

    if(avaliableMaterialeIds.GetAvaliable(&id)) {
        unsigned short minnor = GetIdentifierMinnor(id);
        unsigned short major = GetIdentifierMajor(id);
    
    
        this->MaterialPatch[minnor].mesh[major] = MaterialES3();
        mutex.unlock();
        return id;
    }

    this->MaterialPatch[this->MaterialPatch.size() - 1].mesh[LastAvaliableBatch] = MaterialES3();

    id = EncriptId(this->MaterialPatch.size() - 1, LastAvaliableBatch);
    
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);


    LastAvaliableBatch++;

    if(MATERIALBATCHSIZE <= LastAvaliableBatch) {
        MaterialBatchES3 smb;
        MaterialPatch.push_back(smb);
    
        LastAvaliableBatch = 0;
    }

    mutex.unlock();
    return id;
}

void MaterialCollectionES3::Dellocate(Identifier id) {
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);


    MaterialPatch[minnor].mesh[major].Destroy();

    avaliableMaterialeIds.MakeAvaliable(id);
};

MaterialES3& MaterialCollectionES3::Get(Identifier id) {
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);

    return MaterialPatch[minnor].mesh[major];
}



#endif