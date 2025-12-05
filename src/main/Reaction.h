#ifndef REACTION_H
#define REACTION_H

#include <string>
#include <vector>
#include <map>

struct ReactionComponent {
    std::string formula;        // 化学式
    int stoichiometry;          // 化学计量数
};

class Reaction {
private:
    std::string name;                           // 反应名称
    std::vector<ReactionComponent> reactants;   // 反应物
    std::vector<ReactionComponent> products;    // 产物
    std::string condition;                      // 反应条件
    std::string type;                          // 反应类型
    std::string description;                    // 描述

public:
    Reaction();
    Reaction(const std::string& name, 
             const std::vector<ReactionComponent>& reactants,
             const std::vector<ReactionComponent>& products,
             const std::string& condition,
             const std::string& type,
             const std::string& description);
    
    // Getters
    std::string getName() const { return name; }
    std::vector<ReactionComponent> getReactants() const { return reactants; }
    std::vector<ReactionComponent> getProducts() const { return products; }
    std::string getCondition() const { return condition; }
    std::string getType() const { return type; }
    std::string getDescription() const { return description; }
    
    // 检查给定的化学式列表是否匹配这个反应
    bool matchReactants(const std::vector<std::string>& formulas) const;
    
    // 获取反应方程式字符串
    std::string getEquationString() const;
    
    // 显示反应信息
    void display() const;
    
    // 从文件加载反应数据
    static Reaction loadFromFile(const std::string& filePath);
};

#endif
