# 化学式上下标显示功能 - 实现完成 ?

## ?? 实现总结

已成功实现化学式的上下标Unicode显示功能，所有化学式中的数字现在都会自动转换为下标格式。

## ?? 实现的功能

### 1. FormulaFormatter 类
**文件**: `src/main/FormulaFormatter.h` 和 `src/main/FormulaFormatter.cpp`

**功能**:
- `formatFormula(string)` - 将化学式中的数字转换为下标
- `formatCharge(string)` - 将电荷转换为上标（预留功能）

**转换示例**:
| 输入   | 输出   |
|--------|--------|
| H2     | H?     |
| O2     | O?     |
| H2O    | H?O    |
| CO2    | CO?    |
| CaCO3  | CaCO?  |
| Ca(OH)2| Ca(OH)?|
| NaCl   | NaCl   |

### 2. 集成到所有显示模块

? **Compound.cpp** - 化合物信息显示
```cpp
cout << "化学式: " << FormulaFormatter::formatFormula(formula) << endl;
```

? **Reaction.cpp** - 反应方程式生成
```cpp
equation += FormulaFormatter::formatFormula(reactants[i].formula);
```

? **ReactionSystem.cpp** - 试剂库和反应显示
```cpp
cout << " (" << FormulaFormatter::formatFormula(compound.getFormula()) << ")" << endl;
```

? **main.cpp** - 保持中文字符显示正常

### 3. 编译配置更新

? **CMakeLists.txt** 
- 添加了 `FormulaFormatter.cpp` 到源文件列表
- 设置了 UTF-8 编码支持

? **fix_encoding.ps1**
- 自动修复源文件编码为 UTF-8 with BOM
- 解决MSVC中文字符串编译问题

## ?? 使用效果

### 运行时显示

```
========================================
    欢迎使用化学反应模拟系统
========================================

成功加载 6 种化合物
成功加载 2 个反应规则

========== 试剂库 ==========
[1] 氢气 (H?)
[2] 氧气 (O?)
[3] 水 (H?O)
[4] 钠 (Na)
[5] 氯气 (Cl?)
[6] 氯化钠 (NaCl)
===========================

请选择要混合的试剂（输入编号，用空格分隔，输入0结束）：
示例：1 2（选择氢气和氧气）
> 1 2

========== 反应物 ==========
- 氢气 (H?)
- 氧气 (O?)

========== 找到匹配的反应 ==========
反应名称: 氢氧燃烧反应
反应方程式: 2H? + O? —[点燃]→ 2H?O
反应类型: 化合反应
描述: 氢气在氧气中燃烧生成水

========== 产物 ==========
- 2 × 水 (H?O)

反应成功！
```

## ?? 技术细节

### Unicode下标字符映射

```cpp
const map<char, const char*> subscriptMap = {
    {'0', "?"}, {'1', "?"}, {'2', "?"}, {'3', "?"}, {'4', "?"},
    {'5', "?"}, {'6', "?"}, {'7', "?"}, {'8', "?"}, {'9', "?"}
};
```

### 格式化算法

```cpp
string FormulaFormatter::formatFormula(const string& formula) {
    string result;
    for (size_t i = 0; i < formula.length(); i++) {
        char c = formula[i];
        if (isdigit(c)) {
            // 数字转换为下标
            result += subscriptMap[c];
        } else {
            // 元素符号和括号保持不变
            result += c;
        }
    }
    return result;
}
```

## ? 编译状态

**构建状态**: 生成成功 ?

所有编译错误已解决：
1. ? 创建了 FormulaFormatter 类
2. ? 修复了中文字符串编码问题（UTF-8 with BOM）
3. ? 更新了 CMakeLists.txt
4. ? 所有文件成功编译

## ?? 文档

创建的文档文件：
- ? `FORMULA_FORMATTING.md` - 化学式格式化详细说明
- ? `fix_encoding.ps1` - 编码修复脚本
- ? `README.md` - 更新了项目说明

## ?? 如何使用

1. **编译项目**:
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

2. **运行程序**:
```bash
./ElementReactions
```

3. **如遇编码问题**:
```bash
powershell -ExecutionPolicy Bypass -File fix_encoding.ps1
```

## ?? 视觉效果对比

### 之前
```
[1] 氢气 (H2)
[2] 氧气 (O2)
反应方程式: 2H2 + O2 → 2H2O
```

### 现在
```
[1] 氢气 (H?)
[2] 氧气 (O?)
反应方程式: 2H? + O? —[点燃]→ 2H?O
```

## ?? 未来扩展

已预留了上标功能，可用于：
- 离子电荷显示：Fe??, SO???
- 同位素标记：??C, ???U

只需在 Compound 类中添加电荷属性，即可启用上标功能。

## ? 总结

成功实现了化学式的专业化显示，使用Unicode下标字符，无需额外的字体或图形库，纯文本即可正确显示化学式，大大提升了程序的专业性和可读性！
