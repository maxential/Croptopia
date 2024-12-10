cmake_minimum_required(VERSION 3.15)
project(Croptopia)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

set(VCPKG_TARGET_TRIPLET "x64-mingw-static" CACHE STRING "Target triplet for vcpkg")

include_directories(${PROJECT_SOURCE_DIR}/dependencies/include)
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "Include directory: ${PROJECT_SOURCE_DIR}/dependencies/include")

if(WIN32)
message(STATUS "Running on Windows")
# Specify the vcpkg toolchain and triplet
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file") # Maybe there is a better way to do this?
# Enable WIN32_LEAN_AND_MEAN
add_definitions(-DWIN32_LEAN_AND_MEAN)

elseif(UNIX)

endif()

# Add the executable target
add_executable(Croptopia src/main.cpp
        src/renderer/Renderer.cpp
        src/renderer/Renderer.h
        src/renderer/Window.cpp
        src/renderer/Window.h
        src/utilities/math.h
)

# Add ImGui as a static library
add_library(ImGui STATIC
        dependencies/include/imgui/imgui.cpp
        dependencies/include/imgui/imgui_demo.cpp
        dependencies/include/imgui/imgui_draw.cpp
        dependencies/include/imgui/imgui_tables.cpp
        dependencies/include/imgui/imgui_widgets.cpp
        dependencies/include/imgui/imgui_impl_sdl3.cpp
        dependencies/include/imgui/imgui_impl_sdlrenderer3.cpp
)

# Include ImGui headers
target_include_directories(ImGui PUBLIC dependencies/include/imgui)

# Link ImGui to the executable
target_link_libraries(Croptopia PRIVATE ImGui)

# Use find_package to locate glm
find_package(glm CONFIG REQUIRED)
target_link_libraries(Croptopia PRIVATE glm::glm)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring for Debug mode")
    target_link_libraries(Croptopia PRIVATE ${PROJECT_SOURCE_DIR}/dependencies/lib/Debug/SDL/SDL3.lib)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Configuring for Release mode")
    target_link_libraries(Croptopia PRIVATE ${PROJECT_SOURCE_DIR}/dependencies/lib/Release/SDL/SDL3.lib)
endif()

