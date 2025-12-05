# ElementReactions
一个用C++编写的化学反应模拟系统 - A cpp application which could analyze the reaction of some compounds

## 功能特性

- ? 从文件加载试剂库
- ? 从文件加载反应规则库
- ? 用户可以自定义添加化合物
- ? 用户可以自定义添加反应规则
- ? 自动匹配反应并显示产物
- ? 显示完整的反应方程式和反应条件
- ? **化学式正确显示上下标** (H?O, CO?, CaCO?等)

## 项目结构

```
ElementReactions/
├── src/
│   └── main/
│       ├── main.cpp                # 主程序
│       ├── Compound.h/cpp          # 化合物类
│       ├── Reaction.h/cpp          # 反应类
│       ├── ReactionSystem.h/cpp    # 反应系统类
│       ├── FormulaFormatter.h/cpp  # 化学式格式化工具
│       └── resources/
│           ├── compounds/          # 试剂库文件夹
│           │   ├── TEMPLATE.md    # 化合物文件模板
│           │   ├── hydrogen.txt   # 氢气
│           │   ├── oxygen.txt     # 氧气
│           │   ├── water.txt      # 水
│           │   ├── sodium.txt     # 钠
│           │   ├── chlorine.txt   # 氯气
│           │   └── sodium_chloride.txt  # 氯化钠
│           └── reactions/          # 反应库文件夹
│               ├── TEMPLATE.md    # 反应文件模板
│               ├── hydrogen_oxygen.txt      # 氢氧反应
│               └── sodium_chlorine.txt      # 钠氯反应
├── CMakeLists.txt                  # CMake配置文件
├── fix_encoding.ps1               # 编码修复脚本
└── FORMULA_FORMATTING.md          # 化学式格式化说明
```

## 编译方法

### 使用CMake（推荐）

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### 使用g++直接编译

```bash
g++ -std=c++17 src/main/main.cpp src/main/Compound.cpp src/main/Reaction.cpp src/main/ReactionSystem.cpp src/main/FormulaFormatter.cpp -o ElementReactions
```

## 使用方法

1. 运行程序
2. 查看试剂库中的化合物列表
3. 输入要混合的试剂编号（用空格分隔）
4. 查看反应结果
5. 输入0退出程序

### 示例

```
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

## 化学式上下标显示

系统自动将化学式中的数字转换为下标显示：
- H2 → H?
- O2 → O?  
- H2O → H?O
- CaCO3 → CaCO?
- Ca(OH)2 → Ca(OH)?

详细说明请参考 [FORMULA_FORMATTING.md](FORMULA_FORMATTING.md)

## 添加新化合物

在 `src/main/resources/compounds/` 目录下创建新的 `.txt` 文件，格式如下：

```
名称:化合物名称
化学式:化学式
摩尔质量:数值
状态:固体/液体/气体
描述:描述信息
```

详细说明请参考 `src/main/resources/compounds/TEMPLATE.md`

## 添加新反应

在 `src/main/resources/reactions/` 目录下创建新的 `.txt` 文件，格式如下：

```
反应名称:反应的名称
反应物:化学式1,化学式2,...
反应物化学计量数:数字1,数字2,...
产物:化学式1,化学式2,...
产物化学计量数:数字1,数字2,...
反应条件:条件说明
反应类型:反应类型
描述:反应的描述
```

详细说明请参考 `src/main/resources/reactions/TEMPLATE.md`

### 示例：添加一个新反应

假设要添加碳燃烧反应 `C + O2 → CO2`：

1. 先在 `compounds/` 文件夹中添加碳和二氧化碳的文件
2. 在 `reactions/` 文件夹中创建 `carbon_combustion.txt`：

```
反应名称:碳的燃烧
反应物:C,O2
反应物化学计量数:1,1
产物:CO2
产物化学计量数:1
反应条件:点燃
反应类型:化合反应
描述:碳在氧气中充分燃烧生成二氧化碳
```

## 当前支持的反应

- 氢气 + 氧气 → 水 (2H? + O? → 2H?O)
- 钠 + 氯气 → 氯化钠 (2Na + Cl? → 2NaCl)

## 技术特点

- 使用C++17标准
- 面向对象设计
- 文件驱动的配置系统
- 动态反应匹配算法
- Unicode下标显示化学式
- 跨平台支持（Windows/Linux/macOS）

## 开发注意事项

### 中文编码问题

源代码文件必须保存为 **UTF-8 with BOM** 格式才能正确编译。

如遇到编译错误，运行以下命令修复编码：

```bash
powershell -ExecutionPolicy Bypass -File fix_encoding.ps1
```

详见 [FORMULA_FORMATTING.md](FORMULA_FORMATTING.md)

## 未来扩展

- [ ] 添加更多化学反应
- [ ] 支持化学计量比计算
- [ ] 支持反应条件判断（温度、压力等）
- [ ] 支持多步反应
- [ ] 添加反应热力学数据
- [ ] 支持离子方程式（上标显示电荷）
- [ ] 图形化界面
