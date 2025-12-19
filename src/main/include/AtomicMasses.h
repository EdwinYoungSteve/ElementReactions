#ifndef ATOMICMASSES_H
#define ATOMICMASSES_H

#include <string>
#include <map>

namespace AtomicMasses {
    // Return the atomic mass for an element symbol (e.g., "H", "O").
    // Returns 0.0 if unknown.
    double getAtomicMass(const std::string& symbol);

    // Calculate molar mass (g/mol) given a map of element symbol -> count
    double calculateMass(const std::map<std::string, int>& elements);

    // Return the map of known atomic masses
    const std::map<std::string, double>& getAtomicMassTable();
}

#endif // ATOMICMASSES_H
