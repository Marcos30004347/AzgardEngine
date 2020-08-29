#ifndef ID_QUEUE_H
#define ID_QUEUE_H

#include<queue>
#include<mutex>
#include<list>

using Identifier = unsigned int;

inline Identifier EncriptId(unsigned short minor, unsigned short major) { return ((minor<<16) | ((major) & 0xffff)); }
inline unsigned short GetIdentifierMinnor(Identifier id) { return (id >> 16); }
inline unsigned short GetIdentifierMajor(Identifier id) { return id; }

class IdentifierQueue {
    private:
    std::list<Identifier> invalids;

    static std::mutex mutex;

    public:
    IdentifierQueue();
    ~IdentifierQueue();

    bool GetAvaliable(Identifier* id);
    bool Has(Identifier id);
    void MakeAvaliable(Identifier id);
};


#endif