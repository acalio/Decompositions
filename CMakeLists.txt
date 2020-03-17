cmake_minimum_required(VERSION 3.9.1)

project(deco)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.50 REQUIRED COMPONENTS program_options)
message(STATUS "Boost version: ${Boost_VERSION}")


find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()


set(CMAKE_BUILD_TYPE Debug)

set(SOURCES src/main.cpp 
            src/hDegreeCentrality.cpp
            src/KPeakDecomposition.cpp
            src/DistanceGeneralizedCoreDecomposition.cpp
            src/NeighborCoreness.cpp
            src/EdgeSupportCentrality.cpp
            src/TrussDecomposition.cpp
    )


add_executable(deco ${SOURCES})

target_include_directories(deco 
                PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
                PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)



add_subdirectory(libs/networkit)

target_link_libraries(deco 
                PUBLIC  networkit
                PUBLIC  tlx
                PUBLIC Boost::program_options)
