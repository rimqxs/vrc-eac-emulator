cmake_minimum_required(VERSION 3.29)
project(EOSEmulator)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(dependencies)
link_libraries(minhook)
include_directories(${plog_SOURCE_DIR}/include)

file(GLOB_RECURSE includes_deps
        "includes/*.hpp"
        "includes/*.h"

        "src/common/*.cpp"
        "src/common/*.hpp"
        "src/common/*.h"
)
include_directories(includes)
include_directories(src)

add_subdirectory(src/win)
add_subdirectory(src/linux)
