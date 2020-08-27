#include "definitions.hpp"

#ifndef MODELCOLLECTIONES3_H
#define MODELCOLLECTIONES3_H

#ifdef OPENGLES3_API

#include "DataStructures/Collection.hpp"

#include "ModelES3.hpp"

#include <mutex>

#define MODELBATCHSIZE 10

struct ModelBatchES3 {
    ModelES3 model[MODELBATCHSIZE];
};

 
class ModelCollectionES3 : public Collection<ModelES3> {
    private:
    ModelCollectionES3();
    ~ModelCollectionES3();

    std::vector<ModelBatchES3> modelPatch;

    static std::mutex mutex;

    public:

    static void StartUp();
    static void ShutDown();

    Identifier Insert(ModelES3& ModelData);
    void Delete(Identifier id);
    ModelES3& Get(Identifier id);

    void Destroy();
};




#endif
#endif