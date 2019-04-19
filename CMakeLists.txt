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
add_library(graph STATIC
        source/Graph.cpp
        )

add_library(instance STATIC
        source/Character.cpp
        source/SequenceMovement.cpp
        source/SequenceAttack.cpp
        source/SequenceGameRulesTDM.cpp
        source/GameInstance.cpp
        )

add_library(session STATIC
        source/GameSession.cpp
        )

# Libs include
target_include_directories(graph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(instance PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(session PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Libs links
target_link_libraries(graph Boost::graph)
target_link_libraries(instance graph)
target_link_libraries(session instance)

# Tests
add_executable(graphTest tests/GraphTest.cpp)
add_executable(instanceTest tests/CharacterTest.cpp tests/SequencesTest.cpp)

# Tests links
target_link_libraries(graphTest GTest::main graph)
target_link_libraries(instanceTest GTest::main instance)
