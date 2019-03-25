cmake_minimum_required(VERSION 3.13)
project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-pthread")

# Boost
#set(BOOST_ROOT /home/fktrc/Projects/boost-libs)
#set(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib)
#set(Boost_LIB_PREFIX "lib")
#set (Boost_USE_STATIC_LIBS ON)
#set (Boost_MULTITHREADED ON)
#set (Boost_USE_STATIC_RUNTIME OFF)
#find_package(Boost 1.69.0 COMPONENTS graph REQUIRED)

add_executable(game main.cpp
        source/GameInstance.cpp
        source/Entity.cpp
        source/GameGraph.cpp)

target_include_directories(game
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

#target_link_libraries(multithreads Boost::boost)
