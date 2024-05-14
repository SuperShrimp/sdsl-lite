cmake_minimum_required(VERSION 2.6)
project(TEST)

find_package(PCL REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(TEST airplain_process.cpp)

target_link_libraries (TEST ${PCL_LIBRARIES})

install(TARGETS TEST RUNTIME DESTINATION bin)

