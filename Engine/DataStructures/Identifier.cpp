#include "Identifier.hpp"
#include<mutex>

std::mutex IdentifierQueue::mutex;

IdentifierQueue::IdentifierQueue() {}
IdentifierQueue::~IdentifierQueue() {}

bool IdentifierQueue::GetAvaliable(Identifier* id) {
    mutex.lock();

    if(this->invalids.size()) {
        *id = this->invalids.front();
        this->invalids.pop_front();

        mutex.unlock();
        return true;
    }

    mutex.unlock();
    return false;
}

void IdentifierQueue::MakeAvaliable(Identifier id) {
    mutex.lock();
    this->invalids.push_back(id);
    mutex.unlock();
}

bool IdentifierQueue::Has(Identifier id) {
    for(Identifier i : this->invalids) {
        if(i == id) {
            return true;
        }
    }

    return false; 
}