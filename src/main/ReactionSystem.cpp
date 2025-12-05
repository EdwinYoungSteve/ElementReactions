#include "ReactionSystem.h"
#include "FormulaFormatter.h"
#include <iostream>
#include <filesystem>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

ReactionSystem::ReactionSystem() {}

void ReactionSystem::loadCompounds(const string& directoryPath) {
    compoundLibrary.clear();
    
    try {
        if (!fs::exists(directoryPath)) {
            cerr << "目录不存在: " << directoryPath << endl;
            return;
        }
        
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                Compound compound = Compound::loadFromFile(entry.path().string());
                if (!compound.getName().empty()) {
                    compoundLibrary.push_back(compound);
                }
            }
        }
        
        cout << "成功加载 " << compoundLibrary.size() << " 种化合物" << endl;
    } catch (const exception& e) {
        cerr << "加载化合物时出错: " << e.what() << endl;
    }
}

void ReactionSystem::loadReactions(const string& directoryPath) {
    reactionLibrary.clear();
    
    try {
        if (!fs::exists(directoryPath)) {
            cerr << "目录不存在: " << directoryPath << endl;
            return;
        }
        
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                Reaction reaction = Reaction::loadFromFile(entry.path().string());
                if (!reaction.getName().empty()) {
                    reactionLibrary.push_back(reaction);
                }
            }
        }
        
        cout << "成功加载 " << reactionLibrary.size() << " 个反应规则" << endl;
    } catch (const exception& e) {
        cerr << "加载反应时出错: " << e.what() << endl;
    }
}

void ReactionSystem::displayLibrary() const {
    cout << "\n========== 试剂库 ==========" << endl;
    for (size_t i = 0; i < compoundLibrary.size(); i++) {
        cout << "[" << i + 1 << "] " << compoundLibrary[i].getName() 
             << " (" << FormulaFormatter::formatFormula(compoundLibrary[i].getFormula()) << ")" << endl;
    }
    cout << "===========================\n" << endl;
}

void ReactionSystem::performReaction(const vector<int>& selectedIndices) {
    if (selectedIndices.empty()) {
        cout << "未选择任何试剂！" << endl;
        return;
    }
    
    cout << "\n========== 反应物 ==========" << endl;
    vector<string> selectedFormulas;
    for (int idx : selectedIndices) {
        cout << "- " << compoundLibrary[idx].getName() 
             << " (" << FormulaFormatter::formatFormula(compoundLibrary[idx].getFormula()) << ")" << endl;
        selectedFormulas.push_back(compoundLibrary[idx].getFormula());
    }
    
    // 在反应库中查找匹配的反应
    bool reactionFound = false;
    for (const auto& reaction : reactionLibrary) {
        if (reaction.matchReactants(selectedFormulas)) {
            reactionFound = true;
            
            cout << "\n========== 找到匹配的反应 ==========" << endl;
            reaction.display();
            
            cout << "\n========== 产物 ==========" << endl;
            // 显示产物
            for (const auto& product : reaction.getProducts()) {
                // 在化合物库中查找产物
                for (const auto& compound : compoundLibrary) {
                    if (compound.getFormula() == product.formula) {
                        cout << "- ";
                        if (product.stoichiometry > 1) {
                            cout << product.stoichiometry << " × ";
                        }
                        cout << compound.getName() 
                             << " (" << FormulaFormatter::formatFormula(compound.getFormula()) << ")" << endl;
                        break;
                    }
                }
            }
            
            cout << "\n反应成功！" << endl;
            break;
        }
    }
    
    if (!reactionFound) {
        cout << "\n没有检测到可以发生的反应。" << endl;
        cout << "当前反应库中共有 " << reactionLibrary.size() << " 个反应规则。" << endl;
        
        if (!reactionLibrary.empty()) {
            cout << "\n可用的反应有：" << endl;
            for (const auto& reaction : reactionLibrary) {
                cout << "  - " << reaction.getName() << ": " 
                     << reaction.getEquationString() << endl;
            }
        }
    }
    
    cout << "===========================\n" << endl;
}
