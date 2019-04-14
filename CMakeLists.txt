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
hunter_add_package(Boost COMPONENTS graph system)
find_package(Boost CONFIG REQUIRED graph system)


# Libraries
add_library(navigation STATIC
        source/Graph.cpp
        )

add_library(characters STATIC
        source/Character.cpp
        )

add_library(instance STATIC
        source/GameInstance.cpp
        )

add_library(session STATIC
        source/GameSession.cpp
        )

add_library(server STATIC
        source/TestServer.cpp
        )

add_library(client STATIC
        source/TestClient.cpp
        )

# Libs include
target_include_directories(navigation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(characters PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(instance PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(session PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Libs links
target_link_libraries(navigation Boost::graph)
target_link_libraries(characters navigation)
target_link_libraries(instance characters)
target_link_libraries(session instance)
target_link_libraries(server Boost::system)
target_link_libraries(client Boost::system)

# Tests
add_executable(navigationTest tests/GraphTest.cpp)
add_executable(characterTest tests/CharacterTest.cpp)
add_executable(gameLogicTest tests/GameLogicTest.cpp)

# Tests links
target_link_libraries(navigationTest GTest::main navigation)
target_link_libraries(characterTest GTest::main characters)
target_link_libraries(gameLogicTest GTest::main instance)
