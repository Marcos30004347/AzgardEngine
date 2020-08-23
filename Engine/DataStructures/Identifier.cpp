#include "Identifier.hpp"
#include<mutex>

std::mutex IdentifierQueue::mutex;

IdentifierQueue::IdentifierQueue() {}
IdentifierQueue::~IdentifierQueue() {}

bool IdentifierQueue::GetAvaliable(Identifier* id) {
    mutex.lock();

    if(queue.size()) {
        *id = this->queue.front();
        this->queue.pop();
        mutex.unlock();
        return true;
    }

    mutex.unlock();
    return false;
}

void IdentifierQueue::MakeAvaliable(Identifier id) {
    mutex.lock();
    queue.push(id);
    mutex.unlock();
}