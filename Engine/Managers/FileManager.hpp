#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <fstream>
#include <vector>
#include <string>

enum OpenFileMode {
    BINARY     = std::ios::binary,
    AT_END     = std::ios::ate,
    READONLY   = std::ios::in,
    WRITEONLY  = std::ios::out,
    READWRITE  = std::ios::in | std::ios::out,
    TRUNCATE   = std::ios::trunc,
    APPEND   = std::ios::app,
};

class FileManager {
    friend class Engine; 

    private:

    std::vector<std::fstream> fileStreams;

    static FileManager* gInstance;
    
    FileManager();
    ~FileManager();

    static void StartUp();
    static void ShutDown();


    public:

    static FileManager& GetSingleton(void);
    static FileManager* GetSingletonPtr(void);

    std::string BuildPath(const char* path, ...);

    char* LoadFileToBuffer(std::string path);

    unsigned int OpenFile(std::string path, OpenFileMode mode = READONLY);
    void ResetFile(unsigned int fh);
    void CloseFile(unsigned int fh);
    bool IsFileAtEnd(unsigned int fh);
    char GetFileChar(unsigned int fh);
    std::string GetFileLine(unsigned int fh, unsigned int maxLength = 512);
    std::string GetFileString(unsigned int fh);
};

#endif