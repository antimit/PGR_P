#include "MemoryTracker.hpp"

MemoryTracker::MemoryTracker() {}

MemoryTracker::~MemoryTracker() {
    cleanup(); // Ensure cleanup is called at destruction
}

MemoryTracker& MemoryTracker::getInstance() {
    static MemoryTracker instance;
    return instance;
}

void MemoryTracker::cleanup() {
    for (const auto& deleter : allocatedObjects) {
        deleter.deleter(deleter.ptr); // Call the stored deleter
    }
    allocatedObjects.clear();
}
