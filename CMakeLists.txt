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
        source/SequenceCharacterMovement.cpp
        source/SequenceCharacterAttack.cpp
        source/SequenceGameRulesTDM.cpp
        source/GameInstance.cpp
        )

add_library(match STATIC
        source/Match.cpp
        )

# Libs links
target_link_libraries(graph Boost::graph)
target_link_libraries(instance graph)
target_link_libraries(match instance)

# Tests
add_executable(test-graph tests/GraphTest.cpp)
add_executable(test-character tests/CharacterTest.cpp)
add_executable(test-instance tests/GameInstanceTest.cpp)
add_executable(test-sequence tests/SequenceMovementTest.cpp tests/SequenceAttackTest.cpp)

# Tests links
target_link_libraries(test-graph GTest::main graph)
target_link_libraries(test-character GTest::main instance)
target_link_libraries(test-instance GTest::main instance)
target_link_libraries(test-sequence GTest::main instance)

include_directories(PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(match PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/levels)
target_include_directories(match PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/characters)
