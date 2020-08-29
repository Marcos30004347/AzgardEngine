#include "definitions.hpp"
#ifdef OPENGLES3_SUPORTED

#include "ShaderManagerES3.hpp"
#include <stdio.h>
#include <string.h>

std::mutex ShaderManagerES3::mutex;

IdentifierQueue ShaderManagerES3::avaliableIds;

Identifier ShaderManagerES3::lastGroupAvaliable = 0;

ShaderES3* ShaderManagerES3::data = nullptr;

unsigned int ShaderManagerES3::maxShadersCount = 0;

ShaderManagerES3::ShaderManagerES3() {}

ShaderManagerES3::~ShaderManagerES3() {}

void ShaderManagerES3::StartUp(unsigned int maxShadersCount) {
    ShaderManagerES3::avaliableIds = IdentifierQueue();
    ShaderManagerES3::lastGroupAvaliable = 0;

    ShaderManagerES3::instance = new ShaderManagerES3();

    ShaderManagerES3::maxShadersCount = maxShadersCount;
    ShaderManagerES3::data = (ShaderES3*)malloc(sizeof(ShaderES3)*maxShadersCount);
}

void ShaderManagerES3::ShutDown() {
    ShaderManagerES3::lastGroupAvaliable = 0;
    ShaderManagerES3::maxShadersCount = 0;

    free(ShaderManagerES3::data);
    free(ShaderManagerES3::instance);
}

Identifier ShaderManagerES3::Insert(ShaderES3& shader) {
    mutex.lock();
    Identifier id;

    if(avaliableIds.GetAvaliable(&id)) {
        ShaderManagerES3::data[id] = shader;
        return id;
    } else {
        ShaderManagerES3::data[ShaderManagerES3::lastGroupAvaliable] = shader;
        id = ShaderManagerES3::lastGroupAvaliable;
        ShaderManagerES3::lastGroupAvaliable++;

        if(ShaderManagerES3::lastGroupAvaliable >= ShaderManagerES3::maxShadersCount) {
            ShaderES3* tmp = ShaderManagerES3::data;
            ShaderManagerES3::data = (ShaderES3*)malloc(sizeof(ShaderES3)*(ShaderManagerES3::maxShadersCount + 500));
            memcpy(ShaderManagerES3::data, tmp, sizeof(ShaderES3)*ShaderManagerES3::maxShadersCount);
            ShaderManagerES3::maxShadersCount = ShaderManagerES3::maxShadersCount + 500;
        }
    }

    mutex.unlock();
    return id;
}

void ShaderManagerES3::Delete(Identifier id) {
    ShaderManagerES3::data[id].Destroy();
    avaliableIds.MakeAvaliable(id);
};

ShaderES3& ShaderManagerES3::Get(Identifier id) {
    return ShaderManagerES3::data[id];
}



#endif