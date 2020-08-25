#include "definitions.hpp"
#ifdef OPENGLES3_API

#include "MeshCollectionES3.hpp"


std::mutex MeshCollectionES3::mutex;


MeshCollectionES3::MeshCollectionES3() {
    this->avaliableMesheIds = IdentifierQueue();
    this->lastAvaliableBatch = 0;
    this->meshPatch = std::vector<MeshBatchES3>();
    this->meshPatch.push_back(MeshBatchES3());
}

MeshCollectionES3::~MeshCollectionES3() { this->Destroy(); }

void MeshCollectionES3::Destroy() {}

Identifier MeshCollectionES3::Allocate(Vertice* vertex_array_buffer, unsigned int* index_buffer_buffer, size_t num_vertices) {
    mutex.lock();
    Identifier id;

    if(avaliableMesheIds.GetAvaliable(&id)) {
        unsigned short minnor = GetIdentifierMinnor(id);
        unsigned short major = GetIdentifierMajor(id);
    
    
        this->meshPatch[minnor].mesh[major] = MeshES3(vertex_array_buffer, index_buffer_buffer, num_vertices);
        mutex.unlock();
        return id;
    }

    this->meshPatch[this->meshPatch.size() - 1].mesh[lastAvaliableBatch] = MeshES3(vertex_array_buffer, index_buffer_buffer, num_vertices);

    id = EncriptId(this->meshPatch.size() - 1, lastAvaliableBatch);
    
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);


    lastAvaliableBatch++;

    if(MESHBATCHSIZE <= lastAvaliableBatch) {
        MeshBatchES3 smb;
        meshPatch.push_back(smb);
    
        lastAvaliableBatch = 0;
    }

    mutex.unlock();
    return id;
}

void MeshCollectionES3::Dellocate(Identifier id) {
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);


    meshPatch[minnor].mesh[major].Destroy();

    avaliableMesheIds.MakeAvaliable(id);
};

MeshES3 MeshCollectionES3::Get(Identifier id) {
    unsigned short minnor = GetIdentifierMinnor(id);
    unsigned short major = GetIdentifierMajor(id);

    return meshPatch[minnor].mesh[major];
}



#endif