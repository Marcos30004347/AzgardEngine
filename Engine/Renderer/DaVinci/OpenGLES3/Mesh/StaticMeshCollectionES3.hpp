#include "definitions.hpp"

#ifndef STATICMESHCOLLECTIONES3_H
#ifdef OPENGLES3_API

#define STATICMESHCOLLECTIONES3_H

#include "StaticMeshES3.hpp"

#include<mutex>

#define STATICMESHBATCHSIZE 64


struct StaticMeshBatchES3 {
    StaticMeshES3 mesh[STATICMESHBATCHSIZE];
    StaticMeshBatchES3() {}
};


class StaticMeshCollectionES3 {
    private:

    unsigned short LastAvaliableBatch;

    IdentifierQueue avaliableStaticMesheIds;

    std::vector<StaticMeshBatchES3> StaticMeshPatch;

    static std::mutex mutex;

    public:
    StaticMeshCollectionES3();
    ~StaticMeshCollectionES3();

    Identifier Allocate(StaticVertice* vertex_array_buffer, unsigned int* index_buffer_buffer, size_t num_vertices);
    void Dellocate(Identifier id);
    StaticMeshES3 Get(Identifier id);

    void Destroy();
};




#endif
#endif