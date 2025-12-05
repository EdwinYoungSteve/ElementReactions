#pragma execution_character_set("utf-8")

#include <iostream>
#include <vector>
#include <limits>
#include "ReactionSystem.h"

using namespace std;

int main() {
    ReactionSystem system;
    
    cout << "========================================" << endl;
    cout << "    ��ӭʹ�û�ѧ��Ӧģ��ϵͳ" << endl;
    cout << "========================================\n" << endl;
    
    // ���ػ������
    system.loadCompounds("src/main/resources/compounds");
    
    // ���ط�Ӧ��
    system.loadReactions("src/main/resources/reactions");
    
    while (true) {
        system.displayLibrary();
        
        cout << "��ѡ��Ҫ��ϵ��Լ��������ţ��ÿո�ָ������0��������" << endl;
        cout << "ʾ����1 2��ѡ��������������" << endl;
        cout << "> ";
        
        vector<int> selectedIndices;
        string input;
        getline(cin, input);
        
        // ��������
        size_t pos = 0;
        while (pos < input.length()) {
            // �����ո�
            while (pos < input.length() && input[pos] == ' ') pos++;
            if (pos >= input.length()) break;
            
            // ��ȡ����
            size_t endPos = pos;
            while (endPos < input.length() && input[endPos] != ' ') endPos++;
            
            try {
                int num = stoi(input.substr(pos, endPos - pos));
                if (num == 0) {
                    cout << "\n��лʹ�û�ѧ��Ӧģ��ϵͳ���ټ���" << endl;
                    return 0;
                }
                if (num > 0) {
                    selectedIndices.push_back(num - 1);  // ת��Ϊ0-based����
                }
            } catch (...) {
                // ������Ч����
            }
            
            pos = endPos;
        }
        
        // ִ�з�Ӧ
        system.performReaction(selectedIndices);
        
        cout << "���س�������..." << endl;
        cin.get();
    }
    
    return 0;
}