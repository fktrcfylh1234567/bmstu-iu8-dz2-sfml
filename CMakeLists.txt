cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-pthread")

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.23.31.tar.gz"
        SHA1 "3d94b8522541c4c8eaac606f4c47d09322a8019c"
)

project(game)

# GTest
hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

# Boost
hunter_add_package(Boost COMPONENTS graph)
find_package(Boost CONFIG REQUIRED graph)


# Libraries
add_library(navigation STATIC
        source/GameGraph.cpp
        )

add_library(gameInstance STATIC
        source/Entity.cpp
        source/GameInstance.cpp
        )

add_library(server STATIC
        source/GameServer.cpp
        )

# Tests
add_executable(navigationTest
        tests/GraphTest.cpp
        )

add_executable(gameLogicTest
        tests/GameLogicTest.cpp
        )


# Libs include
target_include_directories(navigation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(gameInstance PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Libs links
target_link_libraries(navigation Boost::graph)
target_link_libraries(gameInstance navigation)
target_link_libraries(server gameInstance)

# Tests links
target_link_libraries(navigationTest GTest::main navigation)
target_link_libraries(gameLogicTest GTest::main gameInstance)
