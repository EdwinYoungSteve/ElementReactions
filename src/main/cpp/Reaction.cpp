#include "Reaction.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Reaction::Reaction() : name(""), equation(""), conditions("") {}

Reaction::Reaction(const std::string& name, const std::string& equation,
                   const std::map<std::string, int>& reactants,
                   const std::map<std::string, int>& products,
                   const std::string& conditions)
    : name(name), equation(equation), reactants(reactants), 
      products(products), conditions(conditions) {}

Reaction Reaction::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return Reaction();
    }
    
    Reaction reaction;
    std::string line;
    bool inReactants = false;
    bool inProducts = false;
    
    // Simple JSON parser
    while (std::getline(file, line)) {
        // Trim whitespace
        size_t start = line.find_first_not_of(" \t\n\r");
        if (start == std::string::npos) continue;
        line = line.substr(start);
        
        // Check for end of blocks
        if ((inReactants || inProducts) && line.find("}") != std::string::npos) {
            inReactants = false;
            inProducts = false;
            continue;
        }
        
        // Parse name
        if (line.find("\"name\"") != std::string::npos) {
            size_t colonPos = line.find(":");
            size_t quoteStart = line.find("\"", colonPos);
            size_t quoteEnd = line.find("\"", quoteStart + 1);
            if (quoteStart != std::string::npos && quoteEnd != std::string::npos) {
                std::string value = line.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
                reaction.setName(value);
            }
        }
        // Parse equation
        else if (line.find("\"equation\"") != std::string::npos) {
            size_t colonPos = line.find(":");
            size_t quoteStart = line.find("\"", colonPos);
            size_t quoteEnd = line.find("\"", quoteStart + 1);
            if (quoteStart != std::string::npos && quoteEnd != std::string::npos) {
                std::string value = line.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
                reaction.setEquation(value);
            }
        }
        // Parse conditions
        else if (line.find("\"conditions\"") != std::string::npos) {
            size_t colonPos = line.find(":");
            size_t quoteStart = line.find("\"", colonPos);
            size_t quoteEnd = line.find("\"", quoteStart + 1);
            if (quoteStart != std::string::npos && quoteEnd != std::string::npos) {
                std::string value = line.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
                reaction.setConditions(value);
            }
        }
        // Parse reactants block
        else if (line.find("\"reactants\"") != std::string::npos) {
            inReactants = true;
            std::map<std::string, int> reactants;
            reaction.setReactants(reactants);
        }
        // Parse products block
        else if (line.find("\"products\"") != std::string::npos) {
            inProducts = true;
            std::map<std::string, int> products;
            reaction.setProducts(products);
        }
        // Parse individual reactants
        else if (inReactants && line.find(":") != std::string::npos) {
            size_t colonPos = line.find(":");
            std::string formula = line.substr(0, colonPos);
            // Remove quotes and whitespace from formula
            size_t quoteStart = formula.find("\"");
            size_t quoteEnd = formula.find("\"", quoteStart + 1);
            if (quoteStart != std::string::npos && quoteEnd != std::string::npos) {
                formula = formula.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
            }
            
            // Get coefficient value
            std::string coeffStr = line.substr(colonPos + 1);
            coeffStr.erase(0, coeffStr.find_first_not_of(" \t"));
            size_t commaPos = coeffStr.find(",");
            if (commaPos != std::string::npos) {
                coeffStr = coeffStr.substr(0, commaPos);
            }
            coeffStr.erase(coeffStr.find_last_not_of(" \t\n\r") + 1);
            
            if (!formula.empty() && !coeffStr.empty()) {
                auto currentReactants = reaction.getReactants();
                currentReactants[formula] = std::stoi(coeffStr);
                reaction.setReactants(currentReactants);
            }
        }
        // Parse individual products
        else if (inProducts && line.find(":") != std::string::npos) {
            size_t colonPos = line.find(":");
            std::string formula = line.substr(0, colonPos);
            // Remove quotes and whitespace from formula
            size_t quoteStart = formula.find("\"");
            size_t quoteEnd = formula.find("\"", quoteStart + 1);
            if (quoteStart != std::string::npos && quoteEnd != std::string::npos) {
                formula = formula.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
            }
            
            // Get coefficient value
            std::string coeffStr = line.substr(colonPos + 1);
            coeffStr.erase(0, coeffStr.find_first_not_of(" \t"));
            size_t commaPos = coeffStr.find(",");
            if (commaPos != std::string::npos) {
                coeffStr = coeffStr.substr(0, commaPos);
            }
            coeffStr.erase(coeffStr.find_last_not_of(" \t\n\r") + 1);
            
            if (!formula.empty() && !coeffStr.empty()) {
                auto currentProducts = reaction.getProducts();
                currentProducts[formula] = std::stoi(coeffStr);
                reaction.setProducts(currentProducts);
            }
        }
    }
    
    file.close();
    return reaction;
}

bool Reaction::canReact(const std::vector<std::string>& compoundFormulas) const {
    // Check if all reactants are present in the compound list
    for (const auto& reactant : reactants) {
        if (std::find(compoundFormulas.begin(), compoundFormulas.end(), 
                     reactant.first) == compoundFormulas.end()) {
            return false;
        }
    }
    return true;
}

void Reaction::display() const {
    std::cout << "Reaction: " << name << std::endl;
    std::cout << "Equation: " << equation << std::endl;
    std::cout << "Conditions: " << conditions << std::endl;
}
