#include "definitions.hpp"
#ifdef OPENGLES3_SUPORTED

#include "ModelManagerES3.hpp"
#include<string.h>

std::mutex ModelManagerES3::mutex;

IdentifierQueue ModelManagerES3::avaliableIds;

Identifier ModelManagerES3::lastGroupAvaliable = 0;

ModelES3* ModelManagerES3::data = nullptr;

unsigned int ModelManagerES3::maxModelesCount = 0;

ModelManagerES3::ModelManagerES3() {}

ModelManagerES3::~ModelManagerES3() {}

void ModelManagerES3::StartUp(unsigned int maxModelesCount) {
    ModelManagerES3::avaliableIds = IdentifierQueue();
    ModelManagerES3::lastGroupAvaliable = 0;

    ModelManagerES3::instance = new ModelManagerES3();

    ModelManagerES3::maxModelesCount = maxModelesCount;
    ModelManagerES3::data = (ModelES3*)malloc(sizeof(ModelES3)*maxModelesCount);
}

void ModelManagerES3::ShutDown() {
    ModelManagerES3::maxModelesCount = 0;
    ModelManagerES3::lastGroupAvaliable = 0;

    free(ModelManagerES3::instance);
    free(ModelManagerES3::data);
}

Identifier ModelManagerES3::Insert(ModelES3& model) {
    mutex.lock();
    Identifier id;
    
    if(avaliableIds.GetAvaliable(&id)) {
        ModelManagerES3::data[id] = model;
    } else {
        ModelManagerES3::data[ModelManagerES3::lastGroupAvaliable] = model;
        id = ModelManagerES3::lastGroupAvaliable;
        ModelManagerES3::lastGroupAvaliable++;

        if(ModelManagerES3::lastGroupAvaliable >= ModelManagerES3::maxModelesCount) {
            ModelES3* tmp = ModelManagerES3::data;
            ModelManagerES3::data = (ModelES3*)malloc(sizeof(ModelES3)*(ModelManagerES3::maxModelesCount + 500));
            memcpy(ModelManagerES3::data, tmp, sizeof(ModelES3)*ModelManagerES3::maxModelesCount);
            ModelManagerES3::maxModelesCount = ModelManagerES3::maxModelesCount + 500;
        }
    }

    mutex.unlock(); 
    return id;
}

void ModelManagerES3::Delete(Identifier id) {
    ModelManagerES3::data[id].Destroy();
    avaliableIds.MakeAvaliable(id);
};

ModelES3& ModelManagerES3::Get(Identifier id) {
    return ModelManagerES3::data[id];
}



#endif