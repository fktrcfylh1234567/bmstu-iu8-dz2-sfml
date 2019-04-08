//
// Created by fktrc on 08.04.19.
//

#include <gtest/gtest.h>
#include "Actor.hpp"

TEST(ActorTest, Spawn) {
    size_t locationSize = 1;
    Graph gameGraph(locationSize);
    bool** location = new bool* [locationSize];
    for (size_t i = 0; i < locationSize; i++) {
        location[i] = new bool[locationSize];
    }
    location[0][0] = true;
    gameGraph.loadLocation(location);

    Actor actor(1, &gameGraph);
    EXPECT_EQ(actor.getId(), 1);
    EXPECT_EQ(actor.isAlive(), false);

    actor.spawn(Point(0, 0));
    EXPECT_EQ(actor.isAlive(), true);
    EXPECT_EQ(actor.getPos(), Point(0, 0));

    actor.setDefaultStats(1000, 10, 10, 200, 10, 5);
    EXPECT_EQ(actor.getHp(), 1000);

    actor.doDamage(250);
    EXPECT_EQ(actor.getHp(), 750);

    actor.doDamage(2500);
    EXPECT_EQ(actor.getHp(), 0);
    EXPECT_EQ(actor.isAlive(), false);

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

    Actor actor(1, &gameGraph);
    actor.spawn(Point(0, 0));
    EXPECT_FALSE(gameGraph.isFree(0, 0));

    actor.setPosition(Point(1, 1));
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

    Actor actor(1, &gameGraph);
    actor.spawn(Point(0, 0));
    Path path = actor.makePath(Point(2, 2));
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

    Actor actor(1, &gameGraph);
    actor.spawn(Point(0, 0));
    actor.setDefaultStats(1000, 10, 10, 200, 10, 5);

    Buff buffEmpty;

    Buff buffSlowDown;
    buffSlowDown.attackSpeed = 0.9;
    buffSlowDown.moveSpeed = 0.9;

    Buff buffStun;
    buffStun.stunned = true;

    actor.addBuff(&buffEmpty);
    actor.updateBuffs();
    EXPECT_EQ(actor.getHeal(), 10);
    EXPECT_EQ(actor.getMoveSpeed(), 10);
    EXPECT_FALSE(actor.isStunned());

    actor.addBuff(&buffSlowDown);
    actor.updateBuffs();
    EXPECT_EQ(actor.getHeal(), 10);
    EXPECT_EQ(actor.getMoveSpeed(), 9);
    EXPECT_EQ(actor.getAttackSpeed(), 9);
    EXPECT_FALSE(actor.isStunned());

    actor.addBuff(&buffStun);
    actor.updateBuffs();
    EXPECT_EQ(actor.getHeal(), 10);
    EXPECT_EQ(actor.getMoveSpeed(), 9);
    EXPECT_EQ(actor.getAttackSpeed(), 9);
    EXPECT_TRUE(actor.isStunned());

    actor.removeBuff(&buffSlowDown);
    actor.updateBuffs();
    EXPECT_EQ(actor.getHeal(), 10);
    EXPECT_EQ(actor.getMoveSpeed(), 10);
    EXPECT_EQ(actor.getAttackSpeed(), 10);
    EXPECT_TRUE(actor.isStunned());

    actor.removeBuff(&buffStun);
    actor.updateBuffs();
    EXPECT_FALSE(actor.isStunned());

    actor.addBuff(&buffSlowDown);
    actor.addBuff(&buffSlowDown);
    actor.addBuff(&buffSlowDown);
    actor.addBuff(&buffSlowDown);
    actor.updateBuffs();
    EXPECT_EQ(actor.getMoveSpeed(), 6);
    EXPECT_EQ(actor.getAttackSpeed(), 6);

    actor.addBuff(&buffStun);
    actor.addBuff(&buffStun);
    actor.addBuff(&buffStun);
    actor.updateBuffs();
    actor.removeBuff(&buffStun);
    actor.removeBuff(&buffStun);
    EXPECT_TRUE(actor.isStunned());

    actor.removeBuff(&buffStun);
    actor.updateBuffs();
    EXPECT_FALSE(actor.isStunned());

    for (size_t i = 0; i < locationSize; i++) {
        delete[] location[i];
    }
    delete[] location;
}
