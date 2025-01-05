#ifndef MEMORYTRACKER_IMPL_HPP
#define MEMORYTRACKER_IMPL_HPP

#include "MemoryTracker.hpp"

// Template implementation for registerAllocation
template <typename T>
void MemoryTracker::registerAllocation(T* obj) {
    allocatedObjects.push_back({static_cast<void*>(obj), [](void* ptr) {
        delete static_cast<T*>(ptr); // Use the original type for deletion
    }});
}

#endif // MEMORYTRACKER_IMPL_HPP
