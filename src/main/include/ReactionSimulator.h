#ifndef REACTION_SIMULATOR_H
#define REACTION_SIMULATOR_H

#include "Compound.h"
#include "Reaction.h"
#include <vector>
#include <string>

/**
 * Main simulator class for managing compounds and reactions
 */
class ReactionSimulator {
private:
    std::vector<Compound> compoundLibrary;
    std::vector<Reaction> reactionLibrary;
    
public:
    ReactionSimulator();
    
    // Load all compounds from directory
    void loadCompounds(const std::string& directory);
    
    // Load all reactions from directory
    void loadReactions(const std::string& directory);
    
    // Display available compounds
    void displayCompounds() const;
    
    // Display available reactions
    void displayReactions() const;
    
    // Get compound by index
    Compound* getCompound(int index);
    
    // Get reaction by index
    const Reaction* getReaction(int index) const;
    
    // Get counts
    size_t getCompoundCount() const { return compoundLibrary.size(); }
    size_t getReactionCount() const { return reactionLibrary.size(); }
    
    // Simulate reaction with selected compounds
    void simulateReaction(const std::vector<int>& selectedIndices);
    
    // Find matching reactions
    std::vector<Reaction*> findMatchingReactions(const std::vector<std::string>& formulas);
};

#endif // REACTION_SIMULATOR_H
