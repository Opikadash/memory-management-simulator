#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <vector>
#include <iostream>
#include <fstream>

enum AllocationStrategy {
    FIRST_FIT,
    BEST_FIT
};

struct MemoryBlock {
    int start;
    int size;
    bool is_free;
};

class MemoryManager {
private:
    int total_size;
    AllocationStrategy strategy;
    std::vector<MemoryBlock> blocks;

public:
    MemoryManager(int size, AllocationStrategy strat);

    int allocate(int size);
    bool deallocate(int start_addr);
    void print_memory();
    double fragmentation();

    void save_state(const std::string& filename);
    void load_state(const std::string& filename);
    void export_to_csv(const std::string& filename);
};

#endif

