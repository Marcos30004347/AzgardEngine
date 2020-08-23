#include "definitions.hpp"
#ifdef OPENGLES3_API

#include "StaticMeshCollectionES3.hpp"


std::mutex StaticMeshCollectionES3::mutex;


StaticMeshCollectionES3::StaticMeshCollectionES3() {
    this->avaliableStaticMesheIds = IdentifierQueue();
    this->LastAvaliableBatch = 0;
    this->StaticMeshPatch = std::vector<StaticMeshBatchES3>();
    this->StaticMeshPatch.push_back(StaticMeshBatchES3());
}

StaticMeshCollectionES3::~StaticMeshCollectionES3() { this->Destroy(); }

void StaticMeshCollectionES3::Destroy() {}

Identifier StaticMeshCollectionES3::Allocate(StaticVertice* vertex_array_buffer, unsigned int* index_buffer_buffer, size_t num_vertices) {
    mutex.lock();
    Identifier id;

    if(avaliableStaticMesheIds.GetAvaliable(&id)) {
        unsigned short minnor = GetIdentifierMinnor(id);
        unsigned short major = GetIdentifierMajor(id);
    
    
        this->StaticMeshPatch[minnor].mesh[major] = StaticMeshES3(vertex_array_buffer, index_buffer_buffer, num_vertices);
        mutex.unlock();
        return id;
    }

    this->StaticMeshPatch[this->StaticMeshPatch.size() - 1].mesh[LastAvaliableBatch] = StaticMeshES3(vertex_array_buffer, index_buffer_buffer, num_vertices);

    id = EncriptId(this->StaticMeshPatch.size() - 1, LastAvaliableBatch);
    
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);


    LastAvaliableBatch++;

    if(STATICMESHBATCHSIZE <= LastAvaliableBatch) {
        StaticMeshBatchES3 smb;
        StaticMeshPatch.push_back(smb);
    
        LastAvaliableBatch = 0;
    }

    mutex.unlock();
    return id;
}

void StaticMeshCollectionES3::Dellocate(Identifier id) {
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);


    StaticMeshPatch[minnor].mesh[major].Destroy();

    avaliableStaticMesheIds.MakeAvaliable(id);
};

StaticMeshES3 StaticMeshCollectionES3::Get(Identifier id) {
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);

    return StaticMeshPatch[minnor].mesh[major];
}



#endif