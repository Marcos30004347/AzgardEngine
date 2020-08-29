#include "definitions.hpp"

#ifndef ShaderManagerES3_H
#ifdef OPENGLES3_SUPORTED

#define ShaderCOLLECTIONES3_H

#include "DataStructures/Identifier.hpp"
#include "DataStructures/Singleton.hpp"
#include "ShaderES3.hpp"

#include<mutex>


class ShaderManagerES3 : public Singleton<ShaderManagerES3> {
    private:

    static IdentifierQueue avaliableIds;

    static Identifier lastGroupAvaliable;

    static ShaderES3* data;
    static unsigned int activesShadersCount;
    static unsigned int maxShadersCount;


    static std::mutex mutex;

    ShaderManagerES3();
    ~ShaderManagerES3();
    
    public:
    static void StartUp(unsigned int maxShadersCount = 2000);
    static void ShutDown();

    Identifier Insert(ShaderES3& shader);
    void Delete(Identifier id);
    ShaderES3& Get(Identifier id);
};




#endif
#endif