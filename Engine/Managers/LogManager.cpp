#include <iostream>
#include <assert.h>
#include <cstdarg>

// TODO: use <thread>
#include <pthread.h>

#include "LogManager.hpp"

pthread_mutex_t mutex;

LogManager* LogManager::gInstance = nullptr;

LogManager::LogManager() {}
LogManager::~LogManager() {}

LogManager* LogManager::GetSingletonPtr(void) {
    assert(LogManager::gInstance);
    return LogManager::gInstance;
}

LogManager& LogManager::GetSingleton(void) {
    assert(LogManager::gInstance);
    return *LogManager::gInstance;
}

void LogManager::StartUp() {
    std::cout << "starting up mesh manager" << std::endl;

    pthread_mutex_init(&mutex, nullptr);

    LogManager::gInstance = new LogManager();
}

void LogManager::ShutDown() {
    std::cout << "shuting down LOG manager" << std::endl;
    delete LogManager::gInstance;
}


struct print_line_args {
    const char* fmt;
    va_list* args;
};

void* print_line(void* t_args) {
    pthread_mutex_lock(&mutex);
    print_line_args* arguments = (print_line_args*)t_args;

    size_t size = snprintf( nullptr, 0, arguments->fmt, *arguments->args ) + 1;

    assert(size);

    char buffer[size];
    vsnprintf (buffer,size,arguments->fmt, *arguments->args);

    std::cout << buffer << std::endl;
    pthread_mutex_unlock(&mutex);

    return nullptr;
}


void LogManager::WriteLine(const char* fmt, ...) {

    pthread_t t;
    va_list args;
    va_start(args, fmt);

    print_line_args t_args;

    t_args.fmt = fmt;
    t_args.args = &args;

    pthread_create(&t, nullptr, print_line, (void*)&t_args);
    pthread_join(t, nullptr);

    va_end(args);
}
