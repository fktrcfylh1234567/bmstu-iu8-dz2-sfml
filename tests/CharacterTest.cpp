//
// Created by fktrc on 08.04.19.
//

#include <gtest/gtest.h>
#include <GameGraph.hpp>
#include <InstanceBuff.hpp>
#include "Character.hpp"

TEST(ActorTest, Spawn) {
    size_t locationSize = 3;
    std::shared_ptr<Graph> graph = std::make_shared<GameGraph>(locationSize);
    std::vector<std::vector<bool>> location = {{true,  true,  true},
                                               {true,  false, false},
                                               {false, false, true}};
    graph->loadLocation(location);

    std::shared_ptr<LocalCharacterStats> stats = std::make_shared<LocalCharacterStats>();
    stats->hp = 1000;
    stats->moveSpeed = 10;

    Character character(1, graph, stats);
    EXPECT_EQ(character.getId(), 1);
    EXPECT_EQ(character.isAlive(), false);

    character.spawn(Point(0, 0));
    EXPECT_EQ(character.isAlive(), true);
    EXPECT_EQ(character.getPos(), Point(0, 0));
    EXPECT_EQ(character.getCurrentStats().hp, 1000);
    EXPECT_EQ(character.getCurrentStats().moveSpeed, 10);

    character.doDamage(250);
    EXPECT_EQ(character.getCurrentStats().hp, 750);

    character.doDamage(2500);
    EXPECT_EQ(character.getCurrentStats().hp, 0);
    EXPECT_EQ(character.isAlive(), false);
}

TEST(ActorTest, Move) {
    size_t locationSize = 2;
    std::shared_ptr<Graph> graph = std::make_shared<GameGraph>(locationSize);
    std::vector<std::vector<bool>> location = {{true, true},
                                               {true, true}};
    graph->loadLocation(location);

    std::shared_ptr<LocalCharacterStats> stats = std::make_shared<LocalCharacterStats>();
    Character character(1, graph, stats);
    character.spawn(Point(0, 0));
    EXPECT_FALSE(graph->isFree(0, 0));

    character.setPosition(Point(1, 1));
    EXPECT_TRUE(graph->isFree(0, 0));
    EXPECT_FALSE(graph->isFree(1, 1));
}

TEST(ActorTest, Path) {
    size_t locationSize = 3;
    std::shared_ptr<Graph> graph = std::make_shared<GameGraph>(locationSize);
    std::vector<std::vector<bool>> location = {{true, true, true},
                                               {true, true, false},
                                               {true, true, true}};
    graph->loadLocation(location);

    std::shared_ptr<LocalCharacterStats> stats = std::make_shared<LocalCharacterStats>();
    Character character(1, graph, stats);
    character.spawn(Point(0, 0));
    Path path = character.makePath(Point(2, 2));
    EXPECT_EQ(path.size(), 5);
    EXPECT_EQ(path[0], Point(0, 0));
    EXPECT_EQ(path[4], Point(2, 2));
}

TEST(ActorTest, BuffStun) {
    size_t locationSize = 1;
    std::shared_ptr<Graph> graph = std::make_shared<GameGraph>(locationSize);
    std::vector<std::vector<bool>> location = {{true}};
    graph->loadLocation(location);
    std::shared_ptr<LocalCharacterStats> stats = std::make_shared<LocalCharacterStats>();
    Character character(1, graph, stats);
    character.spawn(Point(0, 0));

    std::shared_ptr<InstanceBuff> buffStun = std::make_shared<InstanceBuff>();
    buffStun->stunned = true;
    character.addBuff(buffStun);
    EXPECT_EQ(character.activeBuffs.size(), 1);
    EXPECT_TRUE(character.isStunned());

    character.removeBuff(buffStun);
    EXPECT_EQ(character.activeBuffs.size(), 0);

    EXPECT_FALSE(character.isStunned());
}

TEST(ActorTest, BuffSlowDown) {
    size_t locationSize = 1;
    std::shared_ptr<Graph> graph = std::make_shared<GameGraph>(locationSize);
    std::vector<std::vector<bool>> location = {{true}};
    graph->loadLocation(location);

    std::shared_ptr<LocalCharacterStats> stats = std::make_shared<LocalCharacterStats>();
    stats->moveSpeed = 10;

    Character character(1, graph, stats);
    character.spawn(Point(0, 0));

    std::shared_ptr<InstanceBuff> buffSlowDown = std::make_shared<InstanceBuff>();
    buffSlowDown->moveSpeedModifier = 0.9;

    character.addBuff(buffSlowDown);
    EXPECT_EQ(character.getCurrentStats().moveSpeed, 9);
    EXPECT_FALSE(character.isStunned());

    character.removeBuff(buffSlowDown);
    EXPECT_EQ(character.getCurrentStats().moveSpeed, 10);

    // Multiple buffs
    character.addBuff(buffSlowDown);
    character.addBuff(buffSlowDown);
    character.addBuff(buffSlowDown);
    character.addBuff(buffSlowDown);
    EXPECT_EQ(character.getCurrentStats().moveSpeed, 6);

    character.removeBuff(buffSlowDown);
    EXPECT_EQ(character.getCurrentStats().moveSpeed, 7);
}
