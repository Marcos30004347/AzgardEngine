#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

class LogManager {
    friend class Engine; 

    private:
    static LogManager* gInstance;

    LogManager();
    ~LogManager();
    static void StartUp();
    static void ShutDown();

    public:

    static LogManager& GetSingleton(void);
    static LogManager* GetSingletonPtr(void);
    
    void WriteLine(const char* fmt...);
};

#endif