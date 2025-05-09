message(STATUS "Fetching crashlog...")

FetchContent_Declare(
  crashlog
  GIT_REPOSITORY https://github.com/0liteyear/crashlog.git
  GIT_TAG        main
)

FetchContent_MakeAvailable(crashlog)