#pragma execution_character_set("utf-8")

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
            cerr << "Ŀ¼������: " << directoryPath << endl;
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
        
        cout << "�ɹ����� " << compoundLibrary.size() << " �ֻ�����" << endl;
    } catch (const exception& e) {
        cerr << "���ػ�����ʱ����: " << e.what() << endl;
    }
}

void ReactionSystem::loadReactions(const string& directoryPath) {
    reactionLibrary.clear();
    
    try {
        if (!fs::exists(directoryPath)) {
            cerr << "Ŀ¼������: " << directoryPath << endl;
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
        
        cout << "�ɹ����� " << reactionLibrary.size() << " ����Ӧ����" << endl;
    } catch (const exception& e) {
        cerr << "���ط�Ӧʱ����: " << e.what() << endl;
    }
}

void ReactionSystem::displayLibrary() const {
    cout << "\n========== �Լ��� ==========" << endl;
    for (size_t i = 0; i < compoundLibrary.size(); i++) {
        cout << "[" << i + 1 << "] " << compoundLibrary[i].getName() 
             << " (" << FormulaFormatter::formatFormula(compoundLibrary[i].getFormula()) << ")" << endl;
    }
    cout << "===========================\n" << endl;
}

void ReactionSystem::performReaction(const vector<int>& selectedIndices) {
    if (selectedIndices.empty()) {
        cout << "δѡ���κ��Լ���" << endl;
        return;
    }
    
    cout << "\n========== ��Ӧ�� ==========" << endl;
    vector<string> selectedFormulas;
    for (int idx : selectedIndices) {
        cout << "- " << compoundLibrary[idx].getName() 
             << " (" << FormulaFormatter::formatFormula(compoundLibrary[idx].getFormula()) << ")" << endl;
        selectedFormulas.push_back(compoundLibrary[idx].getFormula());
    }
    
    // �ڷ�Ӧ���в���ƥ��ķ�Ӧ
    bool reactionFound = false;
    for (const auto& reaction : reactionLibrary) {
        if (reaction.matchReactants(selectedFormulas)) {
            reactionFound = true;
            
            cout << "\n========== �ҵ�ƥ��ķ�Ӧ ==========" << endl;
            reaction.display();
            
            cout << "\n========== ���� ==========" << endl;
            // ��ʾ����
            for (const auto& product : reaction.getProducts()) {
                // �ڻ�������в��Ҳ���
                for (const auto& compound : compoundLibrary) {
                    if (compound.getFormula() == product.formula) {
                        cout << "- ";
                        if (product.stoichiometry > 1) {
                            cout << product.stoichiometry << " �� ";
                        }
                        cout << compound.getName() 
                             << " (" << FormulaFormatter::formatFormula(compound.getFormula()) << ")" << endl;
                        break;
                    }
                }
            }
            
            cout << "\n��Ӧ�ɹ���" << endl;
            break;
        }
    }
    
    if (!reactionFound) {
        cout << "\nû�м�⵽���Է����ķ�Ӧ��" << endl;
        cout << "��ǰ��Ӧ���й��� " << reactionLibrary.size() << " ����Ӧ����" << endl;
        
        if (!reactionLibrary.empty()) {
            cout << "\n���õķ�Ӧ�У�" << endl;
            for (const auto& reaction : reactionLibrary) {
                cout << "  - " << reaction.getName() << ": " 
                     << reaction.getEquationString() << endl;
            }
        }
    }
    
    cout << "===========================\n" << endl;
}
