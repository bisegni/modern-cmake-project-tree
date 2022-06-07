cmake_minimum_required(VERSION 3.10)

# set the project name
project(
    Tutorial 
    VERSION 1.0
    DESCRIPTION "Modern cmake demo"
    LANGUAGES CXX)
# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

# update configuration include file
configure_file(TutorialConfig.h.in TutorialConfig.h)

# check if need to compile the library
add_subdirectory(LibA)

# add the executable
add_executable(Tutorial main.cpp)
target_link_libraries(Tutorial PUBLIC LibA)
target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           $<INSTALL_INTERFACE:include>
                           )
install(TARGETS Tutorial DESTINATION bin)