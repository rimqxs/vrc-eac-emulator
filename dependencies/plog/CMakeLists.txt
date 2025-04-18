message(STATUS "Fetching plog...")

FetchContent_Declare(
        plog
        GIT_REPOSITORY "https://github.com/SergiusTheBest/plog.git"
        GIT_TAG "origin/master"
)
FetchContent_MakeAvailable(plog)

