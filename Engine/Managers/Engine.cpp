
#include "Engine.hpp"

#include "LogManager.hpp"
#include "MeshManager.hpp"
#include "PlatformManager.hpp"
#include "FileManager.hpp"
#include "EventManager.hpp"
#include "WindowManager.hpp"


Engine::Engine() {
    LogManager::StartUp();
    PlatformManager::StartUp();
    WindowManager::StartUp();
    EventManager::StartUp();
    FileManager::StartUp();
    MeshManager::StartUp();
}

Engine::~Engine() {
    MeshManager::ShutDown();    
    FileManager::ShutDown();    
    EventManager::ShutDown();
    WindowManager::ShutDown();
    PlatformManager::ShutDown();
    LogManager::ShutDown();
}