#include "AtomicMasses.h"

namespace AtomicMasses {

static std::map<std::string, double> atomicMassTable = {
    {"H", 1.00794},
    {"He", 4.002602},
    {"Li", 6.941},
    {"Be", 9.012182},
    {"B", 10.811},
    {"C", 12.0107},
    {"N", 14.0067},
    {"O", 15.9994},
    {"F", 18.9984032},
    {"Ne", 20.1797},
    {"Na", 22.98976928},
    {"Mg", 24.3050},
    {"Al", 26.9815386},
    {"Si", 28.0855},
    {"P", 30.973762},
    {"S", 32.065},
    {"Cl", 35.453},
    {"Ar", 39.948},
    {"K", 39.0983},
    {"Ca", 40.078},
    // Add more as needed
};

double getAtomicMass(const std::string& symbol) {
    auto it = atomicMassTable.find(symbol);
    if (it != atomicMassTable.end()) return it->second;
    return 0.0;
}

const std::map<std::string, double>& getAtomicMassTable() {
    return atomicMassTable;
}

double calculateMass(const std::map<std::string, int>& elements) {
    double total = 0.0;
    for (const auto& kv : elements) {
        double mass = getAtomicMass(kv.first);
        total += mass * static_cast<double>(kv.second);
    }
    return total;
}

} // namespace AtomicMasses
