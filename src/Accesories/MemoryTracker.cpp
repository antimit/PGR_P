#include "MemoryTracker.hpp"

MemoryTracker::MemoryTracker() {}

MemoryTracker::~MemoryTracker() {
    cleanup(); 
}

MemoryTracker& MemoryTracker::getInstance() {
    static MemoryTracker instance;
    return instance;
}

void MemoryTracker::cleanup() {
    for (const auto& deleter : allocatedObjects) {
        deleter.deleter(deleter.ptr); 
    }
    allocatedObjects.clear();
}
