
#include "Engine.hpp"

#include "LogManager.hpp"
#include "MeshManager.hpp"
#include "PlatformManager.hpp"
#include "FileManager.hpp"
#include "EventManager.hpp"
#include "WindowManager.hpp"
#include "DrawManager.hpp"
#include "SceneManager.hpp"
// #include "JobManager.hpp"


Engine::Engine() {
    LogManager::StartUp();
    PlatformManager::StartUp();
    // JobManager::StartUp();
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
    // JobManager::ShutDown();
    PlatformManager::ShutDown();
    LogManager::ShutDown();
}