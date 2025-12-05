cmake_minimum_required(VERSION 3.10)
project(ElementReactions)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加源文件
set(SOURCES
    src/main/main.cpp
    src/main/Compound.cpp
    src/main/Reaction.cpp
    src/main/ReactionSystem.cpp
    src/main/FormulaFormatter.cpp
)

# 添加头文件目录
include_directories(src/main)

# 创建可执行文件
add_executable(ElementReactions ${SOURCES})

# 在Windows上设置UTF-8编码
if(MSVC)
    add_compile_options(/utf-8)
    target_compile_options(ElementReactions PRIVATE /utf-8)
endif()
