# 化学式上下标显示功能实现说明

## 已实现的功能

1. **创建了 FormulaFormatter 类** (`src/main/FormulaFormatter.h/cpp`)
   - 将普通化学式转换为带下标的Unicode格式
   - 例如：H2 → H?, H2O → H?O, CaCO3 → CaCO?
   
2. **集成到所有显示模块**
   - Compound::display() - 显示化合物信息时格式化化学式
   - Reaction::getEquationString() - 生成反应方程式时格式化化学式  
   - ReactionSystem::displayLibrary() - 显示试剂库时格式化化学式
   - ReactionSystem::performReaction() - 显示反应过程时格式化化学式

## 编码问题及解决方案

### 问题描述
MSVC编译器对源代码中的中文字符串字面量处理存在编码问题，即使添加了：
- `#pragma execution_character_set("utf-8")`  
- CMake中的 `/utf-8` 编译选项

仍可能出现"常量中有换行符"等编译错误。

### 解决方案

需要将源代码文件保存为**带BOM的UTF-8格式**。

#### 方法1：使用Visual Studio
1. 打开文件
2. 文件 → 高级保存选项
3. 选择"Unicode (UTF-8 带签名) - 代码页 65001"
4. 保存

#### 方法2：使用PowerShell脚本

创建并运行以下PowerShell脚本 `fix_encoding.ps1`：

```powershell
# 修复源文件编码为UTF-8 with BOM
$files = @(
    "src/main/Compound.cpp",
    "src/main/Reaction.cpp",
    "src/main/ReactionSystem.cpp",
    "src/main/main.cpp"
)

foreach ($file in $files) {
    $content = Get-Content $file -Raw -Encoding UTF8
    $Utf8BomEncoding = New-Object System.Text.UTF8Encoding $True
    [System.IO.File]::WriteAllText((Resolve-Path $file), $content, $Utf8BomEncoding)
    Write-Host "已转换: $file"
}

Write-Host "所有文件已转换为UTF-8 with BOM"
```

运行脚本：
```bash
powershell -ExecutionPolicy Bypass -File fix_encoding.ps1
```

#### 方法3：使用Notepad++
1. 打开文件
2. 编码 → 转为UTF-8-BOM编码
3. 保存

## 使用示例

转换后，化学式将正确显示为：

```
========== 试剂库 ==========
[1] 氢气 (H?)
[2] 氧气 (O?)
[3] 水 (H?O)
[4] 钠 (Na)
[5] 氯气 (Cl?)
[6] 氯化钠 (NaCl)
===========================

反应方程式: 2H? + O? —[点燃]→ 2H?O
```

## 下标字符映射

FormulaFormatter 使用以下Unicode字符：

| 数字 | 下标 | Unicode |
|------|------|---------|
| 0    | ?    | U+2080  |
| 1    | ?    | U+2081  |
| 2    | ?    | U+2082  |
| 3    | ?    | U+2083  |
| 4    | ?    | U+2084  |
| 5    | ?    | U+2085  |
| 6    | ?    | U+2086  |
| 7    | ?    | U+2087  |
| 8    | ?    | U+2088  |
| 9    | ?    | U+2089  |

## 扩展功能

Future: 可以添加上标支持（用于离子电荷）
- 如：Fe??, SO???

FormulaFormatter已经包含上标映射，只需要扩展Compound类添加电荷属性即可。
