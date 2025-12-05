#include "FormulaFormatter.h"
#include <cctype>

using namespace std;

// 下标数字的Unicode映射
const map<char, const char*> FormulaFormatter::subscriptMap = {
    {'0', "?"}, {'1', "?"}, {'2', "?"}, {'3', "?"}, {'4', "?"},
    {'5', "?"}, {'6', "?"}, {'7', "?"}, {'8', "?"}, {'9', "?"}
};

// 上标数字和符号的Unicode映射
const map<char, const char*> FormulaFormatter::superscriptMap = {
    {'0', "?"}, {'1', "?"}, {'2', "?"}, {'3', "?"}, {'4', "?"},
    {'5', "?"}, {'6', "?"}, {'7', "?"}, {'8', "?"}, {'9', "?"},
    {'+', "?"}, {'-', "?"}
};

string FormulaFormatter::formatFormula(const string& formula) {
    string result;
    
    for (size_t i = 0; i < formula.length(); i++) {
        char c = formula[i];
        
        // 如果是数字，转换为下标
        if (isdigit(c)) {
            auto it = subscriptMap.find(c);
            if (it != subscriptMap.end()) {
                result += it->second;
            } else {
                result += c;
            }
        }
        // 如果是括号后面的数字，也转换为下标
        else if (c == '(' || c == ')') {
            result += c;
        }
        // 其他字符（元素符号、大写字母等）直接添加
        else {
            result += c;
        }
    }
    
    return result;
}

string FormulaFormatter::formatCharge(const string& charge) {
    string result;
    
    for (char c : charge) {
        auto it = superscriptMap.find(c);
        if (it != superscriptMap.end()) {
            result += it->second;
        } else {
            result += c;
        }
    }
    
    return result;
}
