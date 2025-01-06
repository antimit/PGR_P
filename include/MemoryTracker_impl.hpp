#ifndef MEMORYTRACKER_IMPL_HPP
#define MEMORYTRACKER_IMPL_HPP

#include "MemoryTracker.hpp"


template <typename T>
void MemoryTracker::registerAllocation(T* obj) {
    allocatedObjects.push_back({static_cast<void*>(obj), [](void* ptr) {
        delete static_cast<T*>(ptr); 
    }});
}

#endif 
