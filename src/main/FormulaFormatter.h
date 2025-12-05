#ifndef FORMULAFORMATTER_H
#define FORMULAFORMATTER_H

#include <string>
#include <map>

class FormulaFormatter {
private:
    // 数字到下标Unicode字符的映射
    static const std::map<char, const char*> subscriptMap;
    
    // 数字到上标Unicode字符的映射
    static const std::map<char, const char*> superscriptMap;

public:
    // 将化学式格式化为带下标的显示格式
    // 例如: "H2O" -> "H?O", "CaCO3" -> "CaCO?"
    static std::string formatFormula(const std::string& formula);
    
    // 将电荷格式化为上标
    // 例如: "+2" -> "??", "-1" -> "?"
    static std::string formatCharge(const std::string& charge);
};

#endif
