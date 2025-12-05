#include <iostream>
#include <vector>
#include <limits>
#include "ReactionSystem.h"

using namespace std;

int main() {
    ReactionSystem system;
    
    cout << "========================================" << endl;
    cout << "    欢迎使用化学反应模拟系统" << endl;
    cout << "========================================\n" << endl;
    
    // 加载化合物库
    system.loadCompounds("src/main/resources/compounds");
    
    // 加载反应库
    system.loadReactions("src/main/resources/reactions");
    
    while (true) {
        system.displayLibrary();
        
        cout << "请选择要混合的试剂（输入编号，用空格分隔，输入0结束）：" << endl;
        cout << "示例：1 2（选择氢气和氧气）" << endl;
        cout << "> ";
        
        vector<int> selectedIndices;
        string input;
        getline(cin, input);
        
        // 解析输入
        size_t pos = 0;
        while (pos < input.length()) {
            // 跳过空格
            while (pos < input.length() && input[pos] == ' ') pos++;
            if (pos >= input.length()) break;
            
            // 读取数字
            size_t endPos = pos;
            while (endPos < input.length() && input[endPos] != ' ') endPos++;
            
            try {
                int num = stoi(input.substr(pos, endPos - pos));
                if (num == 0) {
                    cout << "\n感谢使用化学反应模拟系统！再见！" << endl;
                    return 0;
                }
                if (num > 0) {
                    selectedIndices.push_back(num - 1);  // 转换为0-based索引
                }
            } catch (...) {
                // 忽略无效输入
            }
            
            pos = endPos;
        }
        
        // 执行反应
        system.performReaction(selectedIndices);
        
        cout << "按回车键继续..." << endl;
        cin.get();
    }
    
    return 0;
}