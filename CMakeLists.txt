cmake_minimum_required(VERSION 3.9.1)

project(deco)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()


include_directories(.include .src)


set(CMAKE_BUILD_TYPE Debug)

set(SOURCES src/main.cpp src/hDegreeCentrality.cpp src/DistanceGeneralizedCoreDecomposition.cpp)

add_executable(deco ${SOURCES})

target_link_libraries(deco networkit)
target_link_libraries(deco boost_program_options)