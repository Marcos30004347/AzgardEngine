#include "definitions.hpp"

#ifndef MODELCOLLECTIONES3_H
#define MODELCOLLECTIONES3_H

#ifdef OPENGLES3_API

#include "ModelES3.hpp"

#include <mutex>

#define MODELBATCHSIZE 10

struct ModelBatchES3 {
    ModelES3 model[MODELBATCHSIZE];
};

 
class ModelCollectionES3 {
    private:

    unsigned short lastAvaliableBatch;

    IdentifierQueue avaliableModeleIds;

    std::vector<ModelBatchES3> modelPatch;

    static std::mutex mutex;

    public:
    ModelCollectionES3();
    ~ModelCollectionES3();

    Identifier Allocate(ModelData ModelData);
    void Dellocate(Identifier id);
    ModelES3& Get(Identifier id);

    void Destroy();
};




#endif
#endif