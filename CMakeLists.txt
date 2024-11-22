cmake_minimum_required(VERSION 3.29)
project(EOSEmulator)

set(CMAKE_CXX_STANDARD 26)

########################## FetchContent ################################
include(FetchContent)
FetchContent_Declare(
        minhook
        GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
        GIT_TAG        91cc9466e383d13a43d7cf33c7c8fdccb27095d3
)
FetchContent_Declare(
        plog
        GIT_REPOSITORY "https://github.com/SergiusTheBest/plog.git"
        GIT_TAG "origin/master"
)

FetchContent_MakeAvailable(plog minhook)

link_libraries(minhook)
include_directories(
        ${plog_SOURCE_DIR}/include
)
#############################################################

file(GLOB_RECURSE includes_deps
        "includes/*.cpp"
        "includes/*.hpp"
        "includes/*.h"
)
include_directories(includes)

add_subdirectory(win)
add_subdirectory(linux)
