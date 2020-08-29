#include "definitions.hpp"

#ifndef MODELCOLLECTIONES3_H
#define MODELCOLLECTIONES3_H

#ifdef OPENGLES3_SUPORTED

#include "Singleton.hpp"
#include "Identifier.hpp"

#include "ModelES3.hpp"

#include <mutex>
 
class ModelManagerES3 : public Singleton<ModelManagerES3> {
    private:
    ModelManagerES3();
    ~ModelManagerES3();

    static ModelES3* data;

    static std::mutex mutex;

    static std::vector<Identifier> invalids;

    static IdentifierQueue avaliableIds;

    static unsigned int lastGroupAvaliable;

    static unsigned int maxModelesCount;

    public:

    static void StartUp(unsigned int maxModelsCount = 2000000);
    static void ShutDown();

    Identifier Insert(ModelES3& ModelData);
    void Delete(Identifier id);
    ModelES3& Get(Identifier id);
};


#endif
#endif