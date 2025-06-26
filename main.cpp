// main.cpp
#include "memory_manager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void display_menu() {
    std::cout << "\n=== Memory Management Simulator ===\n";
    std::cout << "1. Allocate Memory\n";
    std::cout << "2. Deallocate Memory\n";
    std::cout << "3. View Memory State\n";
    std::cout << "4. View Fragmentation\n";
    std::cout << "5. Run Random Load Test\n";
    std::cout << "6. Exit\n";
    std::cout << "7. Save Memory State\n";
    std::cout << "8. Load Memory State\n";
    std::cout << "9. Export to CSV\n";
    std::cout << "Enter choice: ";
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::cout << "Choose Allocation Strategy:\n1. First-Fit\n2. Best-Fit\nChoice: ";
    int strategy_choice;
    std::cin >> strategy_choice;
    AllocationStrategy strategy = (strategy_choice == 1) ? FIRST_FIT : BEST_FIT;

    MemoryManager manager(1000, strategy);
    int choice;
    while (true) {
        display_menu();
        std::cin >> choice;

        if (choice == 1) {
            int size;
            std::cout << "Enter size to allocate: ";
            std::cin >> size;
            int addr = manager.allocate(size);
            if (addr == -1) std::cout << "Allocation failed.\n";
            else std::cout << "Allocated at: " << addr << "\n";

        } else if (choice == 2) {
            int addr;
            std::cout << "Enter start address to deallocate: ";
            std::cin >> addr;
            if (manager.deallocate(addr)) std::cout << "Deallocated successfully.\n";
            else std::cout << "Deallocation failed.\n";

        } else if (choice == 3) {
            manager.print_memory();

        } else if (choice == 4) {
            std::cout << "Fragmentation: " << manager.fragmentation() * 100 << "%\n";

        } else if (choice == 5) {
            for (int i = 0; i < 5; ++i) {
                int size = 50 + std::rand() % 200;
                int addr = manager.allocate(size);
                std::cout << "Allocated block of size " << size;
                if (addr != -1) std::cout << " at address " << addr << "\n";
                else std::cout << " (Failed)\n";
            }

            if (std::rand() % 2 == 0) {
                int index = std::rand() % 5;
                std::cout << "Deallocating random block at index " << index << "\n";
                manager.deallocate(index * 50);
            }

        } else if (choice == 6) {
            break;

        } else if (choice == 7) {
            manager.save_state("state.txt");
            std::cout << "State saved to state.txt\n";

        } else if (choice == 8) {
            manager.load_state("state.txt");
            std::cout << "State loaded from state.txt\n";

        } else if (choice == 9) {
            manager.export_to_csv("memory_blocks.csv");
            std::cout << "Exported to memory_blocks.csv\n";

        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}
