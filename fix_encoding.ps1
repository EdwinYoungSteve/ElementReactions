# 修复源文件编码为UTF-8 with BOM
$files = @(
    "src/main/Compound.cpp",
    "src/main/Reaction.cpp",
    "src/main/ReactionSystem.cpp",
    "src/main/main.cpp"
)

foreach ($file in $files) {
    if (Test-Path $file) {
        $content = Get-Content $file -Raw -Encoding UTF8
        $Utf8BomEncoding = New-Object System.Text.UTF8Encoding $True
        [System.IO.File]::WriteAllText((Resolve-Path $file), $content, $Utf8BomEncoding)
        Write-Host "已转换: $file"
    } else {
        Write-Host "文件不存在: $file" -ForegroundColor Red
    }
}

Write-Host "`n所有文件已转换为UTF-8 with BOM" -ForegroundColor Green
Write-Host "现在可以重新编译项目" -ForegroundColor Green
