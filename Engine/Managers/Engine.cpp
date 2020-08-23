
#include "Engine.hpp"

#include "LogManager.hpp"
#include "MeshManager.hpp"
#include "PlatformManager.hpp"
#include "FileManager.hpp"
#include "EventManager.hpp"
#include "WindowManager.hpp"
#include "DrawManager.hpp"
#include "SceneManager.hpp"


Engine::Engine() {
    LogManager::StartUp();
    PlatformManager::StartUp();
    WindowManager::StartUp("Azgard Engine", 1200, 720);
    EventManager::StartUp();
    FileManager::StartUp();
    DrawManager::StartUp();
    SceneManager::StartUp();
    MeshManager::StartUp();
}

Engine::~Engine() {
    MeshManager::ShutDown();    
    SceneManager::ShutDown();
    DrawManager::ShutDown();    
    FileManager::ShutDown();    
    EventManager::ShutDown();
    WindowManager::ShutDown();
    PlatformManager::ShutDown();
    LogManager::ShutDown();
}