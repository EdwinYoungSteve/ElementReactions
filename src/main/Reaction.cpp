#include "Reaction.h"
#include "FormulaFormatter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

Reaction::Reaction() : name(""), condition(""), type(""), description("") {}

Reaction::Reaction(const string& name, 
                   const vector<ReactionComponent>& reactants,
                   const vector<ReactionComponent>& products,
                   const string& condition,
                   const string& type,
                   const string& description)
    : name(name), reactants(reactants), products(products), 
      condition(condition), type(type), description(description) {}

bool Reaction::matchReactants(const vector<string>& formulas) const {
    if (formulas.size() != reactants.size()) {
        return false;
    }
    
    // 创建反应物化学式列表
    vector<string> reactantFormulas;
    for (const auto& r : reactants) {
        reactantFormulas.push_back(r.formula);
    }
    
    // 创建输入化学式的副本用于比较
    vector<string> inputFormulas = formulas;
    
    // 排序后比较
    sort(reactantFormulas.begin(), reactantFormulas.end());
    sort(inputFormulas.begin(), inputFormulas.end());
    
    return reactantFormulas == inputFormulas;
}

string Reaction::getEquationString() const {
    string equation = "";
    
    // 添加反应物
    for (size_t i = 0; i < reactants.size(); i++) {
        if (i > 0) equation += " + ";
        if (reactants[i].stoichiometry > 1) {
            equation += to_string(reactants[i].stoichiometry);
        }
        equation += FormulaFormatter::formatFormula(reactants[i].formula);
    }
    
    // 添加箭头和条件
    if (!condition.empty()) {
        equation += " —[" + condition + "]→ ";
    } else {
        equation += " → ";
    }
    
    // 添加产物
    for (size_t i = 0; i < products.size(); i++) {
        if (i > 0) equation += " + ";
        if (products[i].stoichiometry > 1) {
            equation += to_string(products[i].stoichiometry);
        }
        equation += FormulaFormatter::formatFormula(products[i].formula);
    }
    
    return equation;
}

void Reaction::display() const {
    cout << "反应名称: " << name << endl;
    cout << "反应方程式: " << getEquationString() << endl;
    cout << "反应类型: " << type << endl;
    cout << "描述: " << description << endl;
}

// 辅助函数：分割字符串
static vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        // 去除前后空格
        size_t start = token.find_first_not_of(" \t\r\n");
        size_t end = token.find_last_not_of(" \t\r\n");
        if (start != string::npos && end != string::npos) {
            tokens.push_back(token.substr(start, end - start + 1));
        }
    }
    return tokens;
}

Reaction Reaction::loadFromFile(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "无法打开文件: " << filePath << endl;
        return Reaction();
    }
    
    string name, condition, type, description;
    vector<ReactionComponent> reactants, products;
    vector<string> reactantFormulas, productFormulas;
    vector<int> reactantStoich, productStoich;
    
    string line;
    while (getline(file, line)) {
        size_t colonPos = line.find(':');
        if (colonPos != string::npos) {
            string key = line.substr(0, colonPos);
            string value = line.substr(colonPos + 1);
            
            // 去除前后空格
            size_t start = value.find_first_not_of(" \t\r\n");
            size_t end = value.find_last_not_of(" \t\r\n");
            if (start != string::npos && end != string::npos) {
                value = value.substr(start, end - start + 1);
            }
            
            if (key == "反应名称") {
                name = value;
            } else if (key == "反应物") {
                reactantFormulas = split(value, ',');
            } else if (key == "反应物化学计量数") {
                vector<string> numbers = split(value, ',');
                for (const auto& num : numbers) {
                    reactantStoich.push_back(stoi(num));
                }
            } else if (key == "产物") {
                productFormulas = split(value, ',');
            } else if (key == "产物化学计量数") {
                vector<string> numbers = split(value, ',');
                for (const auto& num : numbers) {
                    productStoich.push_back(stoi(num));
                }
            } else if (key == "反应条件") {
                condition = value;
            } else if (key == "反应类型") {
                type = value;
            } else if (key == "描述") {
                description = value;
            }
        }
    }
    
    file.close();
    
    // 组装反应物
    for (size_t i = 0; i < reactantFormulas.size(); i++) {
        ReactionComponent rc;
        rc.formula = reactantFormulas[i];
        rc.stoichiometry = (i < reactantStoich.size()) ? reactantStoich[i] : 1;
        reactants.push_back(rc);
    }
    
    // 组装产物
    for (size_t i = 0; i < productFormulas.size(); i++) {
        ReactionComponent pc;
        pc.formula = productFormulas[i];
        pc.stoichiometry = (i < productStoich.size()) ? productStoich[i] : 1;
        products.push_back(pc);
    }
    
    return Reaction(name, reactants, products, condition, type, description);
}
