//
// Created by fktrc on 25.03.19.
//

#include <gtest/gtest.h>

#include "GameGraph.hpp"

TEST(Graph, Create) {
    size_t locationSize = 3;
    GameGraph gameGraph(locationSize);

    bool** location = new bool* [locationSize];
    for (size_t i = 0; i < locationSize; i++) {
        location[i] = new bool[locationSize];
    }

    location[0][0] = true;
    location[0][1] = true;
    location[0][2] = true;

    location[1][0] = true;
    location[1][1] = false;
    location[1][2] = false;

    location[2][0] = false;
    location[2][1] = false;
    location[2][2] = true;

    gameGraph.loadLocation(location);

    EXPECT_EQ(gameGraph.isFree({0, 0}), true);
    EXPECT_EQ(gameGraph.isFree({1, 1}), false);
    EXPECT_EQ(gameGraph.isFree({2, 1}), false);
    EXPECT_EQ(gameGraph.isFree({2, 2}), true);

    // Point out of range
    EXPECT_EQ(gameGraph.isFree({20, 10}), false);

    for (size_t i = 0; i < locationSize; i++) {
        delete[] location[i];
    }
    delete[] location;
}

TEST(Graph, Busy) {
    size_t locationSize = 3;
    GameGraph gameGraph(locationSize);

    bool** location = new bool* [locationSize];
    for (size_t i = 0; i < locationSize; i++) {
        location[i] = new bool[locationSize];
    }

    location[0][0] = true;
    location[0][1] = true;
    location[0][2] = true;

    location[1][0] = true;
    location[1][1] = true;
    location[1][2] = true;

    location[2][0] = true;
    location[2][1] = true;
    location[2][2] = true;

    gameGraph.loadLocation(location);

    gameGraph.busyPoint({1, 1});
    gameGraph.busyPoint({1, 2});
    gameGraph.busyPoint({2, 0});
    gameGraph.busyPoint({2, 1});

    EXPECT_EQ(gameGraph.isFree({0, 0}), true);
    EXPECT_EQ(gameGraph.isFree({0, 1}), true);
    EXPECT_EQ(gameGraph.isFree({0, 2}), true);

    EXPECT_EQ(gameGraph.isFree({1, 0}), true);
    EXPECT_EQ(gameGraph.isFree({1, 1}), false);
    EXPECT_EQ(gameGraph.isFree({1, 2}), false);

    EXPECT_EQ(gameGraph.isFree({2, 0}), false);
    EXPECT_EQ(gameGraph.isFree({2, 1}), false);
    EXPECT_EQ(gameGraph.isFree({2, 2}), true);

    for (size_t i = 0; i < locationSize; i++) {
        delete[] location[i];
    }
    delete[] location;
}

TEST(Graph, Release) {
    size_t locationSize = 3;
    GameGraph gameGraph(locationSize);

    bool** location = new bool* [locationSize];
    for (size_t i = 0; i < locationSize; i++) {
        location[i] = new bool[locationSize];
    }

    location[0][0] = false;
    location[0][1] = false;
    location[0][2] = false;

    location[1][0] = false;
    location[1][1] = false;
    location[1][2] = false;

    location[2][0] = false;
    location[2][1] = false;
    location[2][2] = true;

    gameGraph.loadLocation(location);

    gameGraph.releasePoint({1, 1});
    gameGraph.releasePoint({1, 2});
    gameGraph.releasePoint({2, 0});
    gameGraph.releasePoint({2, 1});

    EXPECT_EQ(gameGraph.isFree({0, 0}), false);
    EXPECT_EQ(gameGraph.isFree({0, 1}), false);
    EXPECT_EQ(gameGraph.isFree({0, 2}), false);

    EXPECT_EQ(gameGraph.isFree({1, 0}), false);
    EXPECT_EQ(gameGraph.isFree({1, 1}), true);
    EXPECT_EQ(gameGraph.isFree({1, 2}), true);

    EXPECT_EQ(gameGraph.isFree({2, 0}), true);
    EXPECT_EQ(gameGraph.isFree({2, 1}), true);
    EXPECT_EQ(gameGraph.isFree({2, 2}), true);

    for (size_t i = 0; i < locationSize; i++) {
        delete[] location[i];
    }
    delete[] location;
}

TEST(Graph, Path) {
    size_t locationSize = 3;
    GameGraph gameGraph(locationSize);

    bool** location = new bool* [locationSize];
    for (size_t i = 0; i < locationSize; i++) {
        location[i] = new bool[locationSize];
    }

    location[0][0] = true;
    location[0][1] = true;
    location[0][2] = true;

    location[1][0] = true;
    location[1][1] = true;
    location[1][2] = false;

    location[2][0] = false;
    location[2][1] = false;
    location[2][2] = true;

    gameGraph.loadLocation(location);

    Path path = gameGraph.makePath({1, 0}, {0, 2});
    EXPECT_EQ(path[0], Point(1, 0));
    EXPECT_EQ(path[1], Point(0, 0));
    EXPECT_EQ(path[2], Point(0, 1));
    EXPECT_EQ(path[3], Point(0, 2));

    // Paths not exists
    EXPECT_TRUE(gameGraph.makePath({1, 0}, {1, 0}).empty());
    EXPECT_TRUE(gameGraph.makePath({0, 0}, {2, 2}).empty());
    EXPECT_TRUE(gameGraph.makePath({2, 2}, {0, 0}).empty());

    for (size_t i = 0; i < locationSize; i++) {
        delete[] location[i];
    }
    delete[] location;
}