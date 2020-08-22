#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

enum EventTypes {
    NULL_EVENT = 0,
    QUIT_EVENT,
};

struct Event {
    EventTypes type = NULL_EVENT;
};

class EventManager {
    friend class Engine; 

    private:
    static EventManager* gInstance;

    EventManager();
    ~EventManager();
    static void StartUp();
    static void ShutDown();

    public:

    static EventManager& GetSingleton(void);
    static EventManager* GetSingletonPtr(void);

    void Pool(Event *event);
};

#endif