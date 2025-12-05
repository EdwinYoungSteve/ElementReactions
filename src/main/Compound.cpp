#pragma execution_character_set("utf-8")

#include "Compound.h"
#include "FormulaFormatter.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Compound::Compound() : name(""), formula(""), molarMass(0.0), state(""), description("") {}

Compound::Compound(const string& name, const string& formula, 
                   double molarMass, const string& state, const string& description)
    : name(name), formula(formula), molarMass(molarMass), state(state), description(description) {}

void Compound::display() const {
    cout << "名称: " << name << endl;
    cout << "化学式: " << FormulaFormatter::formatFormula(formula) << endl;
    cout << "摩尔质量: " << molarMass << " g/mol" << endl;
    cout << "状态: " << state << endl;
    cout << "描述: " << description << endl;
}

Compound Compound::loadFromFile(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "无法打开文件: " << filePath << endl;
        return Compound();
    }
    
    string name, formula, state, description;
    double molarMass = 0.0;
    string line;
    
    while (getline(file, line)) {
        size_t colonPos = line.find(':');
        if (colonPos != string::npos) {
            string key = line.substr(0, colonPos);
            string value = line.substr(colonPos + 1);
            
            if (key == "名称") {
                name = value;
            } else if (key == "化学式") {
                formula = value;
            } else if (key == "摩尔质量") {
                molarMass = stod(value);
            } else if (key == "状态") {
                state = value;
            } else if (key == "描述") {
                description = value;
            }
        }
    }
    
    file.close();
    return Compound(name, formula, molarMass, state, description);
}
