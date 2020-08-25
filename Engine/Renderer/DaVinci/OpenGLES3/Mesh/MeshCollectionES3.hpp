#include "definitions.hpp"

#ifndef MESHCOLLECTIONES3_H
#ifdef OPENGLES3_API

#define MESHCOLLECTIONES3_H

#include "MeshES3.hpp"

#include<mutex>

#define MESHBATCHSIZE 64


struct MeshBatchES3 {
    MeshES3 mesh[MESHBATCHSIZE];
    MeshBatchES3() {}
};


class MeshCollectionES3 {
    private:

    unsigned short lastAvaliableBatch;

    IdentifierQueue avaliableMesheIds;

    std::vector<MeshBatchES3> meshPatch;

    static std::mutex mutex;

    public:
    MeshCollectionES3();
    ~MeshCollectionES3();

    Identifier Allocate(Vertice* vertex_array_buffer, unsigned int* index_buffer_buffer, size_t num_vertices);
    void Dellocate(Identifier id);
    MeshES3 Get(Identifier id);

    void Destroy();
};




#endif
#endif