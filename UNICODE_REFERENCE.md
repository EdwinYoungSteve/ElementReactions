# 化学式上下标快速参考

## Unicode下标字符表

| 数字 | 下标 | Unicode | HTML实体 |
|------|------|---------|----------|
| 0    | ?    | U+2080  | &amp;#8320; |
| 1    | ?    | U+2081  | &amp;#8321; |
| 2    | ?    | U+2082  | &amp;#8322; |
| 3    | ?    | U+2083  | &amp;#8323; |
| 4    | ?    | U+2084  | &amp;#8324; |
| 5    | ?    | U+2085  | &amp;#8325; |
| 6    | ?    | U+2086  | &amp;#8326; |
| 7    | ?    | U+2087  | &amp;#8327; |
| 8    | ?    | U+2088  | &amp;#8328; |
| 9    | ?    | U+2089  | &amp;#8329; |

## Unicode上标字符表（预留）

| 字符 | 上标 | Unicode | HTML实体 |
|------|------|---------|----------|
| 0    | ?    | U+2070  | &amp;#8304; |
| 1    | ?    | U+00B9  | &amp;#185;  |
| 2    | ?    | U+00B2  | &amp;#178;  |
| 3    | ?    | U+00B3  | &amp;#179;  |
| 4    | ?    | U+2074  | &amp;#8308; |
| 5    | ?    | U+2075  | &amp;#8309; |
| 6    | ?    | U+2076  | &amp;#8310; |
| 7    | ?    | U+2077  | &amp;#8311; |
| 8    | ?    | U+2078  | &amp;#8312; |
| 9    | ?    | U+2079  | &amp;#8313; |
| +    | ?    | U+207A  | &amp;#8314; |
| -    | ?    | U+207B  | &amp;#8315; |

## 常见化学式示例

### 元素分子
- H? - 氢气
- O? - 氧气
- N? - 氮气
- Cl? - 氯气
- Br? - 溴
- I? - 碘

### 化合物
- H?O - 水
- CO? - 二氧化碳
- NH? - 氨
- CH? - 甲烷
- C?H?OH - 乙醇
- H?SO? - 硫酸
- HNO? - 硝酸
- NaCl - 氯化钠
- CaCO? - 碳酸钙
- Ca(OH)? - 氢氧化钙
- Al?O? - 氧化铝
- Fe?O? - 氧化铁
- KMnO? - 高锰酸钾

### 有机物
- C?H??O? - 葡萄糖
- C??H??O?? - 蔗糖
- CH?COOH - 乙酸
- C?H? - 苯
- C?H? - 乙烯
- C?H? - 丙烷

## 反应方程式示例

### 化合反应
- 2H? + O? → 2H?O
- 2Na + Cl? → 2NaCl
- C + O? → CO?
- 2Mg + O? → 2MgO

### 分解反应
- 2H?O → 2H? + O?
- 2HgO → 2Hg + O?
- CaCO? → CaO + CO?

### 置换反应
- Zn + H?SO? → ZnSO? + H?
- Fe + CuSO? → FeSO? + Cu
- 2Al + 3H?SO? → Al?(SO?)? + 3H?

### 复分解反应
- NaOH + HCl → NaCl + H?O
- BaCl? + H?SO? → BaSO?↓ + 2HCl
- AgNO? + NaCl → AgCl↓ + NaNO?

## 在代码中使用

### C++ (FormulaFormatter)
```cpp
#include "FormulaFormatter.h"

string formula = "H2O";
string formatted = FormulaFormatter::formatFormula(formula);
cout << formatted << endl;  // 输出: H?O
```

### 直接在文本中
在支持Unicode的环境中，可以直接复制粘贴下标字符：
```
H?O
CO?
CaCO?
```

## 箭头符号

| 符号 | Unicode | 说明 |
|------|---------|------|
| →    | U+2192  | 右箭头 |
| ←    | U+2190  | 左箭头 |
| ?    | U+21CC  | 可逆反应 |
| ↑    | U+2191  | 气体生成 |
| ↓    | U+2193  | 沉淀生成 |
| △    | U+25B3  | 加热 |
| —    | U+2014  | 破折号（用于反应条件）|

## 反应条件标注

```
2H? + O? —[点燃]→ 2H?O
CaCO? —[高温]→ CaO + CO?
2KClO? —[MnO?/△]→ 2KCl + 3O?
```

## 特殊符号

| 符号 | Unicode | 说明 |
|------|---------|------|
| ×    | U+00D7  | 乘号 |
| ·    | U+00B7  | 中点（结晶水）|
| ±    | U+00B1  | 正负 |
| ≈    | U+2248  | 约等于 |
| ≥    | U+2265  | 大于等于 |
| ≤    | U+2264  | 小于等于 |

## 实用技巧

1. **Windows**: Win + ; 可打开表情符号面板，搜索"subscript"
2. **Mac**: 使用字符查看器 (Ctrl + Cmd + Space)
3. **Linux**: 使用字符映射表应用
4. **IDE**: 大多数现代IDE支持Unicode输入

## 编码注意事项

确保：
1. 源文件使用 UTF-8 编码（with BOM for MSVC）
2. 终端支持 UTF-8 显示
3. Windows 控制台设置为 UTF-8: `chcp 65001`
