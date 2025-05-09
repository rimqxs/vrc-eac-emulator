message(STATUS "Fetching libhv...")

FetchContent_Declare(
         libhv
         GIT_REPOSITORY "https://github.com/ithewei/libhv"
         GIT_TAG "origin/master"
 )
 FetchContent_MakeAvailable(libhv)