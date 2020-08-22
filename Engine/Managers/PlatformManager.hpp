#ifndef PLATFORM_MANAGER_H
#define PLATFORM_MANAGER_H

enum Platform {
    NONE = 0,
    BROWSER,
    LINUX,
    WINDOWS,
    MACOS
};

class PlatformManager {
    friend class Engine; 

    private:
    static PlatformManager* gInstance;

    PlatformManager();
    ~PlatformManager();
    static void StartUp();
    static void ShutDown();

    public:

    static PlatformManager& GetSingleton(void);
    static PlatformManager* GetSingletonPtr(void);


    const char* GetFileSystemSeparator();
    Platform GetPlatformId();
};

#endif