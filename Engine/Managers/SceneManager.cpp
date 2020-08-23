#include<iostream>
#include<assert.h>

#include "SceneManager.hpp"

SceneManager* SceneManager::gInstance = nullptr;

SceneManager::SceneManager() {}
SceneManager::~SceneManager() {}

SceneManager* SceneManager::GetSingletonPtr(void) {
    assert(SceneManager::gInstance);
    return SceneManager::gInstance;
}

SceneManager& SceneManager::GetSingleton(void) {
    assert(SceneManager::gInstance);
    return *SceneManager::gInstance;
}

void SceneManager::StartUp() {
    std::cout << "starting up scene manager" << std::endl;
    SceneManager::gInstance = new SceneManager();
}

void SceneManager::ShutDown() {
    std::cout << "shuting down scene manager" << std::endl;
    delete SceneManager::gInstance;
}