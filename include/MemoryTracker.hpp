#ifndef MEMORYTRACKER_HPP
#define MEMORYTRACKER_HPP

#include <vector>

class MemoryTracker {
private:
    // Struct to hold a pointer and its deleter function
    struct Deleter {
        void* ptr;
        void (*deleter)(void*);
    };

    std::vector<Deleter> allocatedObjects; // Store pointers and their deleters

    // Private constructor for singleton pattern
    MemoryTracker();

public:
    ~MemoryTracker();

    // Deleted copy constructor and assignment operator to enforce singleton
    MemoryTracker(const MemoryTracker&) = delete;
    MemoryTracker& operator=(const MemoryTracker&) = delete;

    // Get the singleton instance of MemoryTracker
    static MemoryTracker& getInstance();

    // Register a new allocation (templated declaration)
    template <typename T>
    void registerAllocation(T* obj);

    // Clean up all registered objects
    void cleanup();
};

#include "MemoryTracker_impl.hpp" // Inline implementation of templated function

#endif // MEMORYTRACKER_HPP
