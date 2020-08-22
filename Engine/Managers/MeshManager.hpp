#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H

class MeshManager {
    friend class Engine; 

    private:
    static MeshManager* gInstance;

    MeshManager();
    ~MeshManager();
    static void StartUp();
    static void ShutDown();

    public:

    static MeshManager& GetSingleton(void);
    static MeshManager* GetSingletonPtr(void);

};

#endif