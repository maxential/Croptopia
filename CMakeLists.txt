cmake_minimum_required(VERSION 3.15)
project(Croptopia)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

set(VCPKG_TARGET_TRIPLET "x64-mingw-static" CACHE STRING "Target triplet for vcpkg")

if(WIN32)
    message(STATUS "Running on Windows")
# Specify the vcpkg toolchain and triplet
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Enable WIN32_LEAN_AND_MEAN
add_definitions(-DWIN32_LEAN_AND_MEAN)
elseif(UNIX)

endif()

# Add the executable target
add_executable(Croptopia src/main.cpp)

# Use find_package to locate glm
find_package(glm CONFIG REQUIRED)
target_link_libraries(Croptopia PRIVATE glm::glm)
