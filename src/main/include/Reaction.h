#ifndef REACTION_H
#define REACTION_H

#include <string>
#include <vector>
#include <map>

/**
 * Represents a chemical reaction with reactants and products
 */
class Reaction {
private:
    std::string name;           // Reaction name
    std::string equation;       // Full equation (e.g., "2H? + O? ¡ú 2H?O")
    std::map<std::string, int> reactants;  // Reactant formulas and coefficients
    std::map<std::string, int> products;   // Product formulas and coefficients
    std::string conditions;     // Reaction conditions (e.g., "ignition", "room temperature")
    
public:
    Reaction();
    Reaction(const std::string& name, const std::string& equation,
             const std::map<std::string, int>& reactants,
             const std::map<std::string, int>& products,
             const std::string& conditions);
    
    // Getters
    std::string getName() const { return name; }
    std::string getEquation() const { return equation; }
    std::map<std::string, int> getReactants() const { return reactants; }
    std::map<std::string, int> getProducts() const { return products; }
    std::string getConditions() const { return conditions; }
    
    // Setters
    void setName(const std::string& n) { name = n; }
    void setEquation(const std::string& e) { equation = e; }
    void setReactants(const std::map<std::string, int>& r) { reactants = r; }
    void setProducts(const std::map<std::string, int>& p) { products = p; }
    void setConditions(const std::string& c) { conditions = c; }
    
    // Load reaction from JSON file
    static Reaction loadFromFile(const std::string& filename);
    
    // Check if given compounds can undergo this reaction
    bool canReact(const std::vector<std::string>& compoundFormulas) const;
    
    // Display reaction information
    void display() const;
};

#endif // REACTION_H
