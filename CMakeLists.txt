cmake_minimum_required(VERSION 3.20)

project(lira C CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)


get_filename_component(LIRA_ROOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)


add_subdirectory(src)
add_subdirectory(third_party)
add_subdirectory(examples)



#add_library(lira)

