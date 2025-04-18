message(STATUS "Fetching minhook...")

FetchContent_Declare(
        minhook
        GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
        GIT_TAG        "origin/master"
)
FetchContent_MakeAvailable(minhook)
