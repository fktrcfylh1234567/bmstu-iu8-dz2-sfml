//
// Created by fktrc on 08.04.19.
//

#include <gtest/gtest.h>
#include "Character.hpp"

TEST(ActorTest, Spawn) {
    size_t locationSize = 1;
    Graph gameGraph(locationSize);
    bool** location = new bool* [locationSize];
    for (size_t i = 0; i < locationSize; i++) {
        location[i] = new bool[locationSize];
    }
    location[0][0] = true;
    gameGraph.loadLocation(location);

    CharacterStats stats;
    stats.hp = 1000;

    Character character(1, &gameGraph, stats);
    EXPECT_EQ(character.getId(), 1);
    EXPECT_EQ(character.isAlive(), false);

    character.spawn(Point(0, 0));
    EXPECT_EQ(character.isAlive(), true);
    EXPECT_EQ(character.getPos(), Point(0, 0));

    EXPECT_EQ(character.getCurrentStats().hp, 1000);

    character.doDamage(250);
    EXPECT_EQ(character.getCurrentStats().hp, 750);

    character.doDamage(2500);
    EXPECT_EQ(character.getCurrentStats().hp, 0);
    EXPECT_EQ(character.isAlive(), false);

    for (size_t i = 0; i < locationSize; i++) {
        delete[] location[i];
    }
    delete[] location;
}

TEST(ActorTest, Move) {
    size_t locationSize = 2;
    Graph gameGraph(locationSize);
    bool** location = new bool* [locationSize];
    for (size_t i = 0; i < locationSize; i++) {
        location[i] = new bool[locationSize];
    }
    location[0][0] = true;
    location[0][1] = true;
    location[1][0] = true;
    location[1][1] = true;
    gameGraph.loadLocation(location);

    Character character(1, &gameGraph, CharacterStats());
    character.spawn(Point(0, 0));
    EXPECT_FALSE(gameGraph.isFree(0, 0));

    character.setPosition(Point(1, 1));
    EXPECT_TRUE(gameGraph.isFree(0, 0));
    EXPECT_FALSE(gameGraph.isFree(1, 1));

    for (size_t i = 0; i < locationSize; i++) {
        delete[] location[i];
    }
    delete[] location;
}

TEST(ActorTest, Path) {
    size_t locationSize = 3;
    Graph gameGraph(locationSize);
    bool** location = new bool* [locationSize];
    for (size_t i = 0; i < locationSize; i++) {
        location[i] = new bool[locationSize];
    }
    location[0][0] = true;
    location[0][1] = true;
    location[0][2] = true;
    location[1][0] = true;
    location[1][1] = false;
    location[1][2] = true;
    location[2][0] = true;
    location[2][1] = true;
    location[2][2] = true;
    gameGraph.loadLocation(location);

    Character character(1, &gameGraph, CharacterStats());
    character.spawn(Point(0, 0));
    Path path = character.makePath(Point(2, 2));
    EXPECT_EQ(path.size(), 5);
    EXPECT_EQ(path[0], Point(0, 0));
    EXPECT_EQ(path[4], Point(2, 2));

    for (size_t i = 0; i < locationSize; i++) {
        delete[] location[i];
    }
    delete[] location;
}

TEST(ActorTest, Buff) {
    size_t locationSize = 1;
    Graph gameGraph(locationSize);
    bool** location = new bool* [locationSize];
    for (size_t i = 0; i < locationSize; i++) {
        location[i] = new bool[locationSize];
    }
    location[0][0] = true;
    gameGraph.loadLocation(location);

    CharacterStats stats;
    stats.hp = 1000;
    stats.heal = 10;
    stats.moveSpeed = 10;
    stats.attackSpeed = 10;

    Character character(1, &gameGraph, stats);
    character.spawn(Point(0, 0));

    Buff buffEmpty;

    Buff buffSlowDown;
    buffSlowDown.attackSpeedModifier = 0.9;
    buffSlowDown.moveSpeedModifier = 0.9;

    Buff buffStun;
    buffStun.stunned = true;

    character.addBuff(&buffEmpty);
    character.updateBuffs();
    EXPECT_EQ(character.getCurrentStats().heal, 10);
    EXPECT_EQ(character.getCurrentStats().moveSpeed, 10);
    EXPECT_FALSE(character.isStunned());

    character.addBuff(&buffSlowDown);
    character.updateBuffs();
    EXPECT_EQ(character.getCurrentStats().heal, 10);
    EXPECT_EQ(character.getCurrentStats().moveSpeed, 9);
    EXPECT_EQ(character.getCurrentStats().attackSpeed, 9);
    EXPECT_FALSE(character.isStunned());

    character.addBuff(&buffStun);
    character.updateBuffs();
    EXPECT_EQ(character.getCurrentStats().heal, 10);
    EXPECT_EQ(character.getCurrentStats().moveSpeed, 9);
    EXPECT_EQ(character.getCurrentStats().attackSpeed, 9);
    EXPECT_TRUE(character.isStunned());

    character.removeBuff(&buffSlowDown);
    character.updateBuffs();
    EXPECT_EQ(character.getCurrentStats().heal, 10);
    EXPECT_EQ(character.getCurrentStats().moveSpeed, 10);
    EXPECT_EQ(character.getCurrentStats().attackSpeed, 10);
    EXPECT_TRUE(character.isStunned());

    character.removeBuff(&buffStun);
    character.updateBuffs();
    EXPECT_FALSE(character.isStunned());

    character.addBuff(&buffSlowDown);
    character.addBuff(&buffSlowDown);
    character.addBuff(&buffSlowDown);
    character.addBuff(&buffSlowDown);
    character.updateBuffs();
    EXPECT_EQ(character.getCurrentStats().moveSpeed, 6);
    EXPECT_EQ(character.getCurrentStats().attackSpeed, 6);

    character.addBuff(&buffStun);
    character.addBuff(&buffStun);
    character.addBuff(&buffStun);
    character.updateBuffs();
    character.removeBuff(&buffStun);
    character.removeBuff(&buffStun);
    EXPECT_TRUE(character.isStunned());

    character.removeBuff(&buffStun);
    character.updateBuffs();
    EXPECT_FALSE(character.isStunned());

    for (size_t i = 0; i < locationSize; i++) {
        delete[] location[i];
    }
    delete[] location;
}
