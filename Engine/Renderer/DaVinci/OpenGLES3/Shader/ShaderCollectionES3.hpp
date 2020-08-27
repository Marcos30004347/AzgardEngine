#include "definitions.hpp"

#ifndef ShaderCOLLECTIONES3_H
#ifdef OPENGLES3_API

#define ShaderCOLLECTIONES3_H

#include "DataStructures/Collection.hpp"
#include "ShaderES3.hpp"

#include<mutex>

#define SHADERBATCHSIZE 5


struct ShaderBatchES3 {
    ShaderES3 mesh[SHADERBATCHSIZE];
    ShaderBatchES3() {}
};


class ShaderCollectionES3 : public Collection<ShaderES3> {
    private:

    std::vector<ShaderBatchES3> ShaderPatch;

    static std::mutex mutex;

    public:
    ShaderCollectionES3();
    ~ShaderCollectionES3();

    static void StartUp();
    static void ShutDown();

    Identifier Insert(ShaderES3& shader);
    void Delete(Identifier id);
    ShaderES3& Get(Identifier id);

    void Destroy();
};




#endif
#endif