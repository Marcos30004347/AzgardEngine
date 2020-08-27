#include "definitions.hpp"

#ifndef RENDERERCOLLECTIONSES3_H
#define RENDERERCOLLECTIONSES3_H

#ifdef OPENGLES3_API

#include "DataStructures/Singleton.hpp"
#include "DataStructures/Collection.hpp"

#include "Mesh/ModelCollectionES3.hpp"
#include "Camera/CameraCollectionES3.hpp"
#include "Shader/ShaderCollectionES3.hpp"

class CollectionsES3 : public Singleton<CollectionsES3>{
    public:

    static Collection<ModelES3>     *Models;
    static Collection<CameraES3>    *Cameras;
    static Collection<ShaderES3>    *Shaders;

    CollectionsES3();
    ~CollectionsES3();

    static void StartUp();
    static void ShutDown();
};


#endif
#endif