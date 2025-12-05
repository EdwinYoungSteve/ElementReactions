#ifndef REACTIONSYSTEM_H
#define REACTIONSYSTEM_H

#include "Compound.h"
#include "Reaction.h"
#include <vector>
#include <map>
#include <string>

class ReactionSystem {
private:
    std::vector<Compound> compoundLibrary;  // 试剂库
    std::vector<Reaction> reactionLibrary;  // 反应库
    
public:
    ReactionSystem();
    
    // 从资源文件夹加载所有化合物
    void loadCompounds(const std::string& directoryPath);
    
    // 从资源文件夹加载所有反应
    void loadReactions(const std::string& directoryPath);
    
    // 显示试剂库中的所有化合物
    void displayLibrary() const;
    
    // 执行反应
    void performReaction(const std::vector<int>& selectedIndices);
};

#endif
