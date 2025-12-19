#include "ReactionSimulator.h"
#include <iostream>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

ReactionSimulator::ReactionSimulator() {}

void ReactionSimulator::loadCompounds(const std::string& directory) {
    compoundLibrary.clear();
    
    if (!fs::exists(directory)) {
        std::cerr << "Error: Compounds directory does not exist: " << directory << std::endl;
        return;
    }
    
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.path().extension() == ".json") {
            Compound compound = Compound::loadFromFile(entry.path().string());
            if (!compound.getName().empty()) {
                compoundLibrary.push_back(compound);
                std::cout << "Loaded compound: " << compound.getName() << std::endl;
            }
        }
    }
    
    std::cout << "Total compounds loaded: " << compoundLibrary.size() << std::endl;
}

void ReactionSimulator::loadReactions(const std::string& directory) {
    reactionLibrary.clear();
    
    if (!fs::exists(directory)) {
        std::cerr << "Error: Reactions directory does not exist: " << directory << std::endl;
        return;
    }
    
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.path().extension() == ".json") {
            Reaction reaction = Reaction::loadFromFile(entry.path().string());
            if (!reaction.getName().empty()) {
                reactionLibrary.push_back(reaction);
                std::cout << "Loaded reaction: " << reaction.getName() << std::endl;
            }
        }
    }
    
    std::cout << "Total reactions loaded: " << reactionLibrary.size() << std::endl;
}

void ReactionSimulator::displayCompounds() const {
    std::cout << "\n=== Available Compounds ===" << std::endl;
    for (size_t i = 0; i < compoundLibrary.size(); i++) {
        std::cout << "[" << i << "] " << compoundLibrary[i].getName() 
                  << " (" << compoundLibrary[i].getFormula() << ")" << std::endl;
    }
}

void ReactionSimulator::displayReactions() const {
    std::cout << "\n=== Available Reactions ===" << std::endl;
    for (size_t i = 0; i < reactionLibrary.size(); i++) {
        std::cout << "[" << i << "] " << reactionLibrary[i].getName() << std::endl;
        std::cout << "    " << reactionLibrary[i].getEquation() << std::endl;
    }
}

Compound* ReactionSimulator::getCompound(int index) {
    if (index >= 0 && index < static_cast<int>(compoundLibrary.size())) {
        return &compoundLibrary[index];
    }
    return nullptr;
}

const Reaction* ReactionSimulator::getReaction(int index) const {
    if (index >= 0 && index < static_cast<int>(reactionLibrary.size())) {
        return &reactionLibrary[index];
    }
    return nullptr;
}

std::vector<Reaction*> ReactionSimulator::findMatchingReactions(const std::vector<std::string>& formulas) {
    std::vector<Reaction*> matches;
    
    for (auto& reaction : reactionLibrary) {
        if (reaction.canReact(formulas)) {
            matches.push_back(&reaction);
        }
    }
    
    return matches;
}

void ReactionSimulator::simulateReaction(const std::vector<int>& selectedIndices) {
    std::cout << "\n=== Simulating Reaction ===" << std::endl;
    
    // Get selected compounds
    std::vector<std::string> selectedFormulas;
    std::cout << "Selected compounds:" << std::endl;
    for (int index : selectedIndices) {
        Compound* compound = getCompound(index);
        if (compound) {
            std::cout << "  - " << compound->getName() << " (" << compound->getFormula() << ")" << std::endl;
            selectedFormulas.push_back(compound->getFormula());
        }
    }
    
    // Find matching reactions
    auto matches = findMatchingReactions(selectedFormulas);
    
    if (matches.empty()) {
        std::cout << "\nNo reactions found for these compounds." << std::endl;
        return;
    }
    
    std::cout << "\nPossible reactions:" << std::endl;
    for (auto* reaction : matches) {
        std::cout << "\n";
        reaction->display();
        
        // Display products
        std::cout << "Products:" << std::endl;
        for (const auto& product : reaction->getProducts()) {
            // Find product in compound library
            for (const auto& compound : compoundLibrary) {
                if (compound.getFormula() == product.first) {
                    std::cout << "  - " << product.second << " x " 
                             << compound.getName() << " (" << product.first << ")" << std::endl;
                    break;
                }
            }
        }
    }
}
