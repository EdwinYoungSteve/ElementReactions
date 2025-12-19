cmake_minimum_required(VERSION 3.15)
project(ElementReactions)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download ImGui, GLFW via FetchContent
include(FetchContent)

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# Dear ImGui (manual download)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.90.1
)
FetchContent_MakeAvailable(imgui)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src/main/include)
include_directories(${imgui_SOURCE_DIR})
include_directories(${imgui_SOURCE_DIR}/backends)

# ImGui sources
set(IMGUI_SOURCES
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

# Source files
set(SOURCES
    src/main/cpp/main_gui.cpp
    src/main/cpp/Application.cpp
    src/main/cpp/Compound.cpp
    src/main/cpp/AtomicMasses.cpp
    src/main/cpp/Reaction.cpp
    src/main/cpp/ReactionSimulator.cpp
    ${IMGUI_SOURCES}
)

# Executable
add_executable(ElementReactions ${SOURCES})

# Link libraries
target_link_libraries(ElementReactions glfw)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(ElementReactions OpenGL::GL)

# Windows specific libraries
if(WIN32)
    target_link_libraries(ElementReactions gdi32 user32 kernel32)
endif()

# Copy resource files to build directory
add_custom_command(TARGET ElementReactions POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/main/resources
        $<TARGET_FILE_DIR:ElementReactions>/resources
)
