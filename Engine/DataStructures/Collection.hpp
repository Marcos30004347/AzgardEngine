#ifndef COLLECTION_H
#define COLLECTION_H

#include "Singleton.hpp"
#include "Identifier.hpp"

template<typename T>
class Collection : public Singleton<Collection<T>> {
    protected:
    IdentifierQueue avaliableIds;
    unsigned int lastGroupAvaliable;

    public:
    Collection() {
        avaliableIds = IdentifierQueue();
        lastGroupAvaliable = 0;
    }

    ~Collection() {}

    virtual Identifier Insert(T& value) = 0;
    virtual void Delete(Identifier id) = 0;

    virtual T& Get(Identifier id) = 0;
};


#endif