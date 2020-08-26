#include "definitions.hpp"

#ifndef MATERIALCOLLECTIONES3_H
#ifdef OPENGLES3_API

#define MATERIALCOLLECTIONES3_H

#include "DataStructures/Identifier.hpp"
#include "MaterialES3.hpp"

#include<mutex>

#define MATERIALBATCHSIZE 64


struct MaterialBatchES3 {
    MaterialES3 mesh[MATERIALBATCHSIZE];
    MaterialBatchES3() {}
};


class MaterialCollectionES3 {
    private:

    unsigned short LastAvaliableBatch;

    IdentifierQueue avaliableMaterialeIds;

    std::vector<MaterialBatchES3> MaterialPatch;

    static std::mutex mutex;

    public:
    MaterialCollectionES3();
    ~MaterialCollectionES3();

    Identifier Allocate();
    void Dellocate(Identifier id);
    MaterialES3& Get(Identifier id);

    void Destroy();
};




#endif
#endif