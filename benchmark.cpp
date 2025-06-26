#include "memory_manager.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <random>

void benchmarkMemoryManager(int iterations = 1000) {
    MemoryManager mm(1000000); // 1 MB memory

    std::vector<int> allocated_addresses;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 10000);

    auto start = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < iterations; ++i) {
        int size = distribution(generator);
        int addr = mm.allocate(size);
        if (addr != -1) {
            allocated_addresses.push_back(addr);
        }
        // Randomly free some blocks
        if (!allocated_addresses.empty() && i % 10 == 0) {
            int idx = i % allocated_addresses.size();
            mm.free(allocated_addresses[idx]);
            allocated_addresses.erase(allocated_addresses.begin() + idx);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Benchmark completed in " << duration.count() << " seconds\n";
    std::cout << "Current fragmentation: " << mm.calculateFragmentation() << "%\n";
}

int main() {
    benchmarkMemoryManager();
    return 0;
}
