#include<iostream>
#include<assert.h>

#include "MeshManager.hpp"

MeshManager* MeshManager::gInstance = nullptr;

MeshManager::MeshManager() {}
MeshManager::~MeshManager() {}

MeshManager* MeshManager::GetSingletonPtr(void) {
    assert(MeshManager::gInstance);
    return MeshManager::gInstance;
}

MeshManager& MeshManager::GetSingleton(void) {
    assert(MeshManager::gInstance);
    return *MeshManager::gInstance;
}

void MeshManager::StartUp() {
    std::cout << "starting up mesh manager" << std::endl;
    MeshManager::gInstance = new MeshManager();
}

void MeshManager::ShutDown() {
    std::cout << "shuting down mesh manager" << std::endl;
    delete MeshManager::gInstance;
}