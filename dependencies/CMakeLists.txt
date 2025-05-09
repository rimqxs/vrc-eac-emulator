include(FetchContent)

message(STATUS "Installing all required dependencies")
add_subdirectory(plog)
add_subdirectory(minhook)
add_subdirectory(libhv)