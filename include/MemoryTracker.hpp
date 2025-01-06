#ifndef MEMORYTRACKER_HPP
#define MEMORYTRACKER_HPP

#include <vector>

class MemoryTracker {
private:
    
    struct Deleter {
        void* ptr;
        void (*deleter)(void*);
    };

    std::vector<Deleter> allocatedObjects; 

    
    MemoryTracker();

public:
    ~MemoryTracker();

    
    MemoryTracker(const MemoryTracker&) = delete;
    MemoryTracker& operator=(const MemoryTracker&) = delete;

    
    static MemoryTracker& getInstance();

    
    template <typename T>
    void registerAllocation(T* obj);

    
    void cleanup();
};

#include "MemoryTracker_impl.hpp" 

#endif 
