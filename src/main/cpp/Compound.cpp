#include "Compound.h"
#include "AtomicMasses.h"
#include <iostream>
#include <fstream>
#include <sstream>

Compound::Compound() : name(""), formula(""), state("") {}

Compound::Compound(const std::string& name, const std::string& formula,
                   const std::map<std::string, int>& elements, const std::string& state)
    : name(name), formula(formula), elements(elements), state(state) {}

Compound Compound::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return Compound();
    }
    
    Compound compound;
    std::string line;
    bool inElements = false;
    
    // Simple JSON parser (basic implementation)
    while (std::getline(file, line)) {
        // Trim whitespace
        size_t start = line.find_first_not_of(" \t\n\r");
        if (start == std::string::npos) continue;
        line = line.substr(start);
        
        // Check for end of elements block
        if (inElements && line.find("}") != std::string::npos) {
            inElements = false;
            continue;
        }
        
        // Parse name
        if (line.find("\"name\"") != std::string::npos) {
            size_t colonPos = line.find(":");
            size_t quoteStart = line.find("\"", colonPos);
            size_t quoteEnd = line.find("\"", quoteStart + 1);
            if (quoteStart != std::string::npos && quoteEnd != std::string::npos) {
                std::string value = line.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
                compound.setName(value);
            }
        }
        // Parse formula
        else if (line.find("\"formula\"") != std::string::npos) {
            size_t colonPos = line.find(":");
            size_t quoteStart = line.find("\"", colonPos);
            size_t quoteEnd = line.find("\"", quoteStart + 1);
            if (quoteStart != std::string::npos && quoteEnd != std::string::npos) {
                std::string value = line.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
                compound.setFormula(value);
            }
        }
        // Parse state
        else if (line.find("\"state\"") != std::string::npos) {
            size_t colonPos = line.find(":");
            size_t quoteStart = line.find("\"", colonPos);
            size_t quoteEnd = line.find("\"", quoteStart + 1);
            if (quoteStart != std::string::npos && quoteEnd != std::string::npos) {
                std::string value = line.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
                compound.setState(value);
            }
        }
        // Parse elements block
        else if (line.find("\"elements\"") != std::string::npos) {
            inElements = true;
            std::map<std::string, int> elements;
            compound.setElements(elements);
        }
        // Parse individual elements
        else if (inElements && line.find(":") != std::string::npos) {
            size_t colonPos = line.find(":");
            std::string element = line.substr(0, colonPos);
            // Remove quotes and whitespace from element name
            size_t quoteStart = element.find("\"");
            size_t quoteEnd = element.find("\"", quoteStart + 1);
            if (quoteStart != std::string::npos && quoteEnd != std::string::npos) {
                element = element.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
            }
            
            // Get count value
            std::string countStr = line.substr(colonPos + 1);
            // Remove whitespace and comma
            countStr.erase(0, countStr.find_first_not_of(" \t"));
            size_t commaPos = countStr.find(",");
            if (commaPos != std::string::npos) {
                countStr = countStr.substr(0, commaPos);
            }
            countStr.erase(countStr.find_last_not_of(" \t\n\r") + 1);
            
            if (!element.empty() && !countStr.empty()) {
                auto currentElements = compound.getElements();
                currentElements[element] = std::stoi(countStr);
                compound.setElements(currentElements);
            }
        }
    }
    
    file.close();
    return compound;
}

void Compound::display() const {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Formula: " << formula << std::endl;
    std::cout << "State: " << state << std::endl;
    std::cout << "Elements: ";
    for (const auto& pair : elements) {
        std::cout << pair.first << ":" << pair.second << " ";
    }
    std::cout << std::endl;
}

double Compound::getMolarMass() const {
    return AtomicMasses::calculateMass(elements);
}
