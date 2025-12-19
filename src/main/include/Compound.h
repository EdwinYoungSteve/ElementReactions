#ifndef COMPOUND_H
#define COMPOUND_H

#include <string>
#include <map>

/**
 * Represents a chemical compound with its formula and element composition
 */
class Compound {
private:
    std::string name;           // Common name (e.g., "Water")
    std::string formula;        // Chemical formula (e.g., "H?O")
    std::map<std::string, int> elements;  // Element composition (e.g., {"H": 2, "O": 1})
    std::string state;          // Physical state (gas, liquid, solid, aqueous)
    
public:
    Compound();
    Compound(const std::string& name, const std::string& formula, 
             const std::map<std::string, int>& elements, const std::string& state);
    
    // Getters
    std::string getName() const { return name; }
    std::string getFormula() const { return formula; }
    std::map<std::string, int> getElements() const { return elements; }
    std::string getState() const { return state; }
    
    // Setters
    void setName(const std::string& n) { name = n; }
    void setFormula(const std::string& f) { formula = f; }
    void setElements(const std::map<std::string, int>& e) { elements = e; }
    void setState(const std::string& s) { state = s; }
    
    // Load compound from JSON file
    static Compound loadFromFile(const std::string& filename);
    
    // Display compound information
    void display() const;

    // Calculate molar mass (g/mol)
    double getMolarMass() const;
};

#endif // COMPOUND_H
