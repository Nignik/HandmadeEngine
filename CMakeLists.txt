cmake_minimum_required (VERSION 3.20)

project ("HandmadeEngine")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(HandmadeEngine WIN32 ${SOURCES})
target_include_directories(HandmadeEngine PUBLIC include)