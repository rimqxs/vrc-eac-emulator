cmake_minimum_required(VERSION 3.29)
project(EOSEmulator)
set(CMAKE_CXX_STANDARD 26)

option(SAFETYHOOK_FETCH_ZYDIS "" ON)

########################## FetchContent ################################
include(FetchContent)
FetchContent_Declare(
        safetyhook
        GIT_REPOSITORY "https://github.com/cursey/safetyhook.git"
        GIT_TAG "origin/main"
)
FetchContent_Declare(
        plog
        GIT_REPOSITORY "https://github.com/SergiusTheBest/plog.git"
        GIT_TAG "origin/master"
)
FetchContent_MakeAvailable(safetyhook plog)

link_libraries(safetyhook)
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
