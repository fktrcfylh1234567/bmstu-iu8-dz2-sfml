cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-pthread")

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.23.31.tar.gz"
        SHA1 "3d94b8522541c4c8eaac606f4c47d09322a8019c"
)

project(game)

add_subdirectory(tools/sfml)

# GTest
hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

# Boost
hunter_add_package(Boost COMPONENTS graph system thread)
find_package(Boost CONFIG REQUIRED graph system thread)

# JSON
hunter_add_package(nlohmann_json)
find_package(nlohmann_json CONFIG REQUIRED)


# Libraries
add_library(graph STATIC
        source/Graph.cpp
        )

add_library(server STATIC
        source/ConnectionServer.cpp
        source/Server.cpp
        )

add_library(client STATIC
        source/ConnectionClient.cpp
        source/Client.cpp
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

add_library(SessionServer STATIC
        source/SessionSever.cpp
        )

add_library(SessionClient STATIC
        source/SessionClient.cpp
        )

# Libs links
target_link_libraries(graph Boost::graph)
target_link_libraries(server Boost::system Boost::thread)
target_link_libraries(client Boost::system Boost::thread)
target_link_libraries(instance graph)
target_link_libraries(match instance)
target_link_libraries(SessionServer match server nlohmann_json::nlohmann_json)
target_link_libraries(SessionClient client nlohmann_json::nlohmann_json)


# Executables
add_executable(runServer main_server.cpp)
add_executable(runClient main_client.cpp)

target_link_libraries(runServer gameServer)
target_link_libraries(runClient clientn)


# Tests
add_executable(testGraph tests/GraphTest.cpp)
add_executable(testCharacter tests/CharacterTest.cpp)
add_executable(testInstance tests/GameInstanceTest.cpp)
add_executable(testSequence tests/SequenceMovementTest.cpp tests/SequenceAttackTest.cpp)

# Tests links
target_link_libraries(testGraph GTest::main graph)
target_link_libraries(testCharacter GTest::main instance)
target_link_libraries(testInstance GTest::main instance)
target_link_libraries(testSequence GTest::main instance)

include_directories(PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tools/json)
target_include_directories(match PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/levels)
target_include_directories(match PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/characters)
