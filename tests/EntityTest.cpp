//
// Created by fktrc on 26.03.19.
//

#include <gtest/gtest.h>

#include "Entity.hpp"

TEST(Entity, Spawn) {
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
    Entity entity(&gameGraph);
    EXPECT_EQ(entity.isAlive(), false);

    // Invalid point
    entity.spawn(Point(2, 1));
    EXPECT_EQ(entity.isAlive(), false);

    // Valid point
    entity.spawn(Point(0, 1));
    EXPECT_EQ(entity.isAlive(), true);
    EXPECT_EQ(entity.getPos(), Point(0, 1));
    EXPECT_EQ(gameGraph.isFree(entity.getPos()), false);

    entity.destroy();
    EXPECT_EQ(entity.isAlive(), false);
    EXPECT_EQ(gameGraph.isFree(entity.getPos()), true);

    for (size_t i = 0; i < locationSize; i++) {
        delete[] location[i];
    }
    delete[] location;
}

TEST(Entity, Movement) {
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
    Entity entity(&gameGraph);
    entity.spawn(Point(0, 1));

    // Invalid point
    entity.setPosition(Point(2, 1));
    EXPECT_EQ(entity.isAlive(), true);
    EXPECT_EQ(entity.getPos(), Point(0, 1));
    EXPECT_EQ(gameGraph.isFree(entity.getPos()), false);

    // Valid point
    entity.setPosition(Point(0, 2));
    EXPECT_EQ(entity.isAlive(), true);
    EXPECT_EQ(entity.getPos(), Point(0, 2));
    EXPECT_EQ(gameGraph.isFree(entity.getPos()), false);
    EXPECT_EQ(gameGraph.isFree(Point(0, 1)), true);

    for (size_t i = 0; i < locationSize; i++) {
        delete[] location[i];
    }
    delete[] location;
}
