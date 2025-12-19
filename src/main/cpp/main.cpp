#include "ReactionSimulator.h"
#include <iostream>
#include <vector>
#include <limits>

void displayMenu() {
    std::cout << "\n=== Chemical Reaction Simulator ===" << std::endl;
    std::cout << "1. Display all compounds" << std::endl;
    std::cout << "2. Display all reactions" << std::endl;
    std::cout << "3. Simulate reaction" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    ReactionSimulator simulator;
    
    // Load compound and reaction libraries
    std::cout << "Loading compound library..." << std::endl;
    simulator.loadCompounds("resources/compounds");
    
    std::cout << "\nLoading reaction library..." << std::endl;
    simulator.loadReactions("resources/reactions");
    
    // Main loop
    while (true) {
        displayMenu();
        
        int choice;
        std::cin >> choice;
        
        // Clear input buffer
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                simulator.displayCompounds();
                break;
                
            case 2:
                simulator.displayReactions();
                break;
                
            case 3: {
                simulator.displayCompounds();
                std::cout << "\nEnter compound indices (space-separated, -1 to finish): ";
                
                std::vector<int> selectedIndices;
                int index;
                while (std::cin >> index && index != -1) {
                    selectedIndices.push_back(index);
                }
                
                // Clear input buffer
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                if (!selectedIndices.empty()) {
                    simulator.simulateReaction(selectedIndices);
                } else {
                    std::cout << "No compounds selected." << std::endl;
                }
                break;
            }
            
            case 4:
                std::cout << "Exiting..." << std::endl;
                return 0;
                
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    
    return 0;
}
