// memory_manager.cpp
#include "memory_manager.h"
#include <algorithm>

MemoryManager::MemoryManager(int size, AllocationStrategy strat) {
    total_size = size;
    strategy = strat;
    blocks.push_back({0, size, true});
}

int MemoryManager::allocate(int size) {
    int index = -1;
    if (strategy == FIRST_FIT) {
        for (int i = 0; i < blocks.size(); ++i) {
            if (blocks[i].is_free && blocks[i].size >= size) {
                index = i;
                break;
            }
        }
    } else if (strategy == BEST_FIT) {
        int best_size = total_size + 1;
        for (int i = 0; i < blocks.size(); ++i) {
            if (blocks[i].is_free && blocks[i].size >= size && blocks[i].size < best_size) {
                best_size = blocks[i].size;
                index = i;
            }
        }
    }

    if (index == -1) return -1;

    MemoryBlock& blk = blocks[index];
    int alloc_start = blk.start;
    if (blk.size == size) {
        blk.is_free = false;
    } else {
        blocks.insert(blocks.begin() + index + 1, {blk.start + size, blk.size - size, true});
        blk.size = size;
        blk.is_free = false;
    }
    return alloc_start;
}

bool MemoryManager::deallocate(int start_addr) {
    for (auto& blk : blocks) {
        if (blk.start == start_addr && !blk.is_free) {
            blk.is_free = true;
            return true;
        }
    }
    return false;
}

void MemoryManager::print_memory() {
    std::cout << "\n--- Memory Blocks ---\n";
    for (const auto& blk : blocks) {
        std::cout << "Start: " << blk.start << ", Size: " << blk.size
                  << ", Status: " << (blk.is_free ? "Free" : "Allocated") << "\n";
    }
}

double MemoryManager::fragmentation() {
    int free_space = 0;
    int largest_free_block = 0;
    for (const auto& blk : blocks) {
        if (blk.is_free) {
            free_space += blk.size;
            if (blk.size > largest_free_block) {
                largest_free_block = blk.size;
            }
        }
    }
    if (free_space == 0) return 0.0;
    return 1.0 - (double)largest_free_block / free_space;
}

void MemoryManager::save_state(const std::string& filename) {
    std::ofstream out(filename);
    for (const auto& blk : blocks) {
        out << blk.start << " " << blk.size << " " << blk.is_free << "\n";
    }
}

void MemoryManager::load_state(const std::string& filename) {
    std::ifstream in(filename);
    blocks.clear();
    int start, size;
    bool is_free;
    while (in >> start >> size >> is_free) {
        blocks.push_back({start, size, is_free});
    }
}

void MemoryManager::export_to_csv(const std::string& filename) {
    std::ofstream csv(filename);
    csv << "Start,Size,Status\n";
    for (const auto& blk : blocks) {
        csv << blk.start << "," << blk.size << "," << (blk.is_free ? "Free" : "Allocated") << "\n";
    }
}

