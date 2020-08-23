#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

class SceneManager {
    friend class Engine; 

    private:
    static SceneManager* gInstance;

    SceneManager();
    ~SceneManager();
    static void StartUp();
    static void ShutDown();

    public:

    static SceneManager& GetSingleton(void);
    static SceneManager* GetSingletonPtr(void);

};

#endif