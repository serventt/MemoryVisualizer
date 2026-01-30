#include <cstdint>
#include <iostream>
#include <vector>
#include <random>

// this is just to make compiler and clangd shutup
#define IGNORE_WARN [[maybe_unused]]

// stuff that tracks memory
static size_t totalAllocated{};
IGNORE_WARN int64_t currentFrame{};
std::vector<int*> leakTracker{};
static std::random_device rd;
static std::mt19937 gen(rd());

// this stuff is used in the graph function, feel free to delete/change
IGNORE_WARN float leakUnlikelyhood = 3.f; // the higher this is the less leaks happen
IGNORE_WARN static int simulationSpeed = 1000; // the speed at which the drawing happens
IGNORE_WARN bool outputAllocation = false; // disable/enable output when allocating
IGNORE_WARN float graphScalingHorizontal = 50.f; // bigger = more horizontal points
IGNORE_WARN float graphScalingVertical = 20.f; // bigger = more vertical points
IGNORE_WARN float pointWidth = 10.f; // width of every point in the graph
IGNORE_WARN int64_t graphDevidedBy = 5; // this is how many frames between each point in the graph

/*
* here we are  overloading the new and delete operators, im keeping their main functionality
* of allocating and deallocating memory and adding tracking the total allocated memory in
* totalAllocated
*/
void* operator new(size_t size) {
    totalAllocated += size;
    if (outputAllocation) std::cout << "allocating " << size << " bytes of memory." << std::endl;
    void* block = malloc( sizeof(size_t) + size);
    *(size_t*)block = size;
    return (char*) block + sizeof(size_t);
}

void operator delete(void* memory) noexcept {
    if (outputAllocation) std::cout << "deallocating memory." << std::endl;
    size_t* memSize = (size_t*) ((char*)memory - sizeof(size_t));
    if (totalAllocated > *memSize) totalAllocated -= *memSize;
    free(memSize);
}

void graph() {
    std::uniform_int_distribution<int> coinFlip(0, (int) leakUnlikelyhood);
    bool action = coinFlip(gen);
    if (!action) {
        leakTracker.push_back(new int());
    } else {
        if (leakTracker.size() >= 1) {
            std::uniform_real_distribution<float> dist(0,(float) leakTracker.size() - 1);
            leakTracker.erase(leakTracker.begin() + (const __int64) dist(gen));
        }
    }
}
