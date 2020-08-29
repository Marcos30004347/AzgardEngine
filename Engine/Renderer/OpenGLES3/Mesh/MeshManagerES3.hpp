#include "definitions.hpp"

#ifndef MESHCOLLECTIONES3_H
#define MESHCOLLECTIONES3_H

#ifdef OPENGLES3_SUPORTED

#include "Singleton.hpp"
#include "Identifier.hpp"

#include "MeshES3.hpp"

#include <mutex>
 
class MeshManagerES3 : public Singleton<MeshManagerES3> {
    private:
    MeshManagerES3();
    ~MeshManagerES3();

    static MeshES3* data;

    static std::mutex mutex;

    static std::vector<Identifier> invalids;

    static IdentifierQueue avaliableIds;

    static unsigned int lastGroupAvaliable;

    static unsigned int maxMeshesCount;

    public:

    static void StartUp(unsigned int maxMeshsCount = 2000000);
    static void ShutDown();

    Identifier Insert(MeshES3& MeshData);
    void Delete(Identifier id);
    MeshES3& Get(Identifier id);
};


#endif
#endif