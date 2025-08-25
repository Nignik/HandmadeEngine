cmake_minimum_required (VERSION 3.26)

project ("HandmadeEngine")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(dependencies.cmake)

FetchContent_MakeAvailable(OTemplate)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(HandmadeEngine WIN32 ${SOURCES})
target_include_directories(HandmadeEngine PUBLIC include)

target_link_libraries(HandmadeEngine PRIVATE OTemplate)