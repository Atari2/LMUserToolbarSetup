# CMakeList.txt : CMake project for UserToolbarSetup, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
set(CMAKE_CXX_STANDARD 17)
add_executable (UserToolbarSetup "UserToolbarSetup.cpp" "UserToolbarSetup.h")

# TODO: Add tests and install targets if needed.
