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
    cout << "\xE5\x90\x8D\xE7\xA7\xB0: " << name << endl;  // "名称: "
    cout << "\xE5\x8C\x96\xE5\xAD\xA6\xE5\xBC\x8F: " << FormulaFormatter::formatFormula(formula) << endl;  // "化学式: "
    cout << "\xE6\x91\xA9\xE5\xB0\x94\xE8\xB4\xA8\xE9\x87\x8F: " << molarMass << " g/mol" << endl;  // "摩尔质量: "
    cout << "\xE7\x8A\xB6\xE6\x80\x81: " << state << endl;  // "状态: "
    cout << "\xE6\x8F\x8F\xE8\xBF\xB0: " << description << endl;  // "描述: "
}

Compound Compound::loadFromFile(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "\xE6\x97\xA0\xE6\xB3\x95\xE6\x89\x93\xE5\xBC\x80\xE6\x96\x87\xE4\xBB\xB6: " << filePath << endl;  // "无法打开文件: "
        return Compound();
    }
    
    string name, formula, state, description;
    double molarMass = 0.0;
    string line;
    
    const string key_name = "\xE5\x90\x8D\xE7\xA7\xB0";  // "名称"
    const string key_formula = "\xE5\x8C\x96\xE5\xAD\xA6\xE5\xBC\x8F";  // "化学式"
    const string key_molar = "\xE6\x91\xA9\xE5\xB0\x94\xE8\xB4\xA8\xE9\x87\x8F";  // "摩尔质量"
    const string key_state = "\xE7\x8A\xB6\xE6\x80\x81";  // "状态"
    const string key_desc = "\xE6\x8F\x8F\xE8\xBF\xB0";  // "描述"
    
    while (getline(file, line)) {
        size_t colonPos = line.find(':');
        if (colonPos != string::npos) {
            string key = line.substr(0, colonPos);
            string value = line.substr(colonPos + 1);
            
            if (key == key_name) {
                name = value;
            } else if (key == key_formula) {
                formula = value;
            } else if (key == key_molar) {
                molarMass = stod(value);
            } else if (key == key_state) {
                state = value;
            } else if (key == key_desc) {
                description = value;
            }
        }
    }
    
    file.close();
    return Compound(name, formula, molarMass, state, description);
}
