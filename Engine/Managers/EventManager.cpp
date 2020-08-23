#include<iostream>
#include<assert.h>

#include "EventManager.hpp"
#include "definitions.hpp"

#ifdef SDL2_IMP

#include <SDL2/SDL.h>
SDL_Event sdl2_event;
#endif

EventManager* EventManager::gInstance = nullptr;

EventManager::EventManager() {}
EventManager::~EventManager() {}

EventManager* EventManager::GetSingletonPtr(void) {
    assert(EventManager::gInstance);
    return EventManager::gInstance;
}

EventManager& EventManager::GetSingleton(void) {
    assert(EventManager::gInstance);
    return *EventManager::gInstance;
}

void EventManager::StartUp() {
    std::cout << "starting up event manager" << std::endl;
    EventManager::gInstance = new EventManager();
}

void EventManager::ShutDown() {
    std::cout << "shuting down event manager" << std::endl;
    delete EventManager::gInstance;
}

bool EventManager::Pool(Event *event) {
    #ifdef SDL2_IMP

    int pedding = SDL_PollEvent(&sdl2_event);
    
    switch (sdl2_event.type)
    {
    case SDL_QUIT:
        event->type = QUIT_EVENT;
        break;
    
    default:
        event->type = NULL_EVENT;
        break;
    }

    #else

    #error IMPLEMENTATION NOT DEFINED

    #endif

    return pedding;
}