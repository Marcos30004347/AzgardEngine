#ifndef SINGLETON_H
#define SINGLETON_H

template<typename T>
class Singleton {
    public:
    static T* instance;
    inline static T* GetSingletonPtr() { return instance; }
};

template<typename T>
T* Singleton<T>::instance = nullptr;

#endif