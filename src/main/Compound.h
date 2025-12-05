#ifndef COMPOUND_H
#define COMPOUND_H

#include <string>
#include <map>

class Compound {
private:
    std::string name;           // 名称
    std::string formula;        // 化学式
    double molarMass;           // 摩尔质量
    std::string state;          // 状态
    std::string description;    // 描述

public:
    Compound();
    Compound(const std::string& name, const std::string& formula, 
             double molarMass, const std::string& state, const std::string& description);
    
    // Getters
    std::string getName() const { return name; }
    std::string getFormula() const { return formula; }
    double getMolarMass() const { return molarMass; }
    std::string getState() const { return state; }
    std::string getDescription() const { return description; }
    
    // 显示化合物信息
    void display() const;
    
    // 从文件加载化合物数据
    static Compound loadFromFile(const std::string& filePath);
};

#endif
