#include <iostream>
#include <assert.h>
#include <stdarg.h>
#include <sstream>
#include "FileManager.hpp"
#include "PlatformManager.hpp"

FileManager* FileManager::gInstance = nullptr;

FileManager::FileManager() {}
FileManager::~FileManager() {}

FileManager* FileManager::GetSingletonPtr(void) {
    assert(FileManager::gInstance);
    return FileManager::gInstance;
}

FileManager& FileManager::GetSingleton(void) {
    assert(FileManager::gInstance);
    return *FileManager::gInstance;
}

void FileManager::StartUp() {
    std::cout << "starting up file manager" << std::endl;
    FileManager::gInstance = new FileManager();
}

void FileManager::ShutDown() {
    std::cout << "shuting down file manager" << std::endl;
    delete FileManager::gInstance;
}

std::string FileManager::BuildPath(const char* path, ...) {
    const char* current;

    va_list vl;
    va_start(vl, path);

    current = path;

    std::string result = std::string(path);

    PlatformManager* gPlatformManager = PlatformManager::GetSingletonPtr();
   
    current = va_arg(vl, const char*);

    while(current) {
        result = result + gPlatformManager->GetFileSystemSeparator() + current;

        current = va_arg(vl, const char*);
    }

    va_end(vl);
    std::cout << result.c_str() << std::endl;
    return result;
}


unsigned int FileManager::OpenFile(std::string path, OpenFileMode mode) {
    this->fileStreams.push_back(std::fstream());
    this->fileStreams[this->fileStreams.size() - 1].open(path, (std::ios_base::openmode)mode);
    return this->fileStreams.size() - 1;
}

void FileManager::CloseFile(unsigned int fh) {
    assert(
        this->fileStreams.size() > fh
        && this->fileStreams[fh].is_open()
    );

    this->fileStreams[fh].close();
}

void FileManager::ResetFile(unsigned int fh) {
    assert(
        this->fileStreams.size() > fh
        && this->fileStreams[fh].is_open()
    );

    this->fileStreams[fh].clear();
    this->fileStreams[fh].seekg(0);
}

bool FileManager::IsFileAtEnd(unsigned int fh){
    assert(
        this->fileStreams.size() > fh
        && this->fileStreams[fh].is_open()
    );

    return this->fileStreams[fh].eof();
}


std::string FileManager::GetFileString(unsigned int fh) {
    assert(
        this->fileStreams.size() > fh
        && this->fileStreams[fh].is_open()
    );

    std::stringstream vShaderStream;

    vShaderStream << this->fileStreams[fh].rdbuf();

    return vShaderStream.str();
}

std::string FileManager::GetFileLine(unsigned int fh, unsigned int maxLength) {
    assert(
        this->fileStreams.size() > fh
        && this->fileStreams[fh].is_open()
    );

    char buff[maxLength];
    this->fileStreams[fh].getline(buff, maxLength);
    return std::string(buff);
}

char* FileManager::LoadFileToBuffer(std::string path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);

    std::streamsize size = file.tellg();

    file.seekg(0, std::ios::beg);

    std::vector<char> *buffer = new std::vector<char>(size);
    file.read(buffer->data(), size);
    file.close();

    assert(buffer->data());
    return buffer->data();
}