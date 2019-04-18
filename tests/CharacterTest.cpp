//
// Created by fktrc on 08.04.19.
//

#include <gtest/gtest.h>
#include <Graph.hpp>
#include <BuffInstance.hpp>
#include "Character.hpp"

TEST(ActorTest, Spawn) {
    size_t locationSize = 3;
    std::shared_ptr<IGraph> graph = std::make_shared<Graph>(locationSize);
    std::vector<std::vector<bool>> location = {{true,  true,  true},
                                               {true,  false, false},
                                               {false, false, true}};
    graph->loadLocation(location);

    std::shared_ptr<CharacterStatsInstance> stats = std::make_shared<CharacterStatsInstance>();
    stats->setHp(1000);
    stats->setMoveSpeed(10);

    Character character(1, graph, stats);
    EXPECT_EQ(character.getId(), 1);
    EXPECT_EQ(character.isAlive(), false);

    character.spawn(Point(0, 0));
    EXPECT_EQ(character.isAlive(), true);
    EXPECT_EQ(character.getPos(), Point(0, 0));
    EXPECT_EQ(character.getCurrentStats().getHp(), 1000);
    EXPECT_EQ(character.getCurrentStats().getMoveSpeed(), 10);

    character.doDamage(250);
    EXPECT_EQ(character.getCurrentStats().getHp(), 750);

    character.doDamage(2500);
    EXPECT_EQ(character.getCurrentStats().getHp(), 0);
    EXPECT_EQ(character.isAlive(), false);
}

TEST(ActorTest, Move) {
    size_t locationSize = 2;
    std::shared_ptr<IGraph> graph = std::make_shared<Graph>(locationSize);
    std::vector<std::vector<bool>> location = {{true, true},
                                               {true, true}};
    graph->loadLocation(location);

    std::shared_ptr<CharacterStatsInstance> stats = std::make_shared<CharacterStatsInstance>();
    Character character(1, graph, stats);
    character.spawn(Point(0, 0));
    EXPECT_FALSE(graph->isFree(0, 0));

    character.setPosition(Point(1, 1));
    EXPECT_TRUE(graph->isFree(0, 0));
    EXPECT_FALSE(graph->isFree(1, 1));
}

TEST(ActorTest, Path) {
    size_t locationSize = 3;
    std::shared_ptr<IGraph> graph = std::make_shared<Graph>(locationSize);
    std::vector<std::vector<bool>> location = {{true, true, true},
                                               {true, true, false},
                                               {true, true, true}};
    graph->loadLocation(location);

    std::shared_ptr<CharacterStatsInstance> stats = std::make_shared<CharacterStatsInstance>();
    Character character(1, graph, stats);
    character.spawn(Point(0, 0));
    Path path = character.makePath(Point(2, 2));
    EXPECT_EQ(path.size(), 5);
    EXPECT_EQ(path[0], Point(0, 0));
    EXPECT_EQ(path[4], Point(2, 2));
}

TEST(ActorTest, BuffSlowDown) {
    size_t locationSize = 1;
    std::shared_ptr<IGraph> graph = std::make_shared<Graph>(locationSize);
    std::vector<std::vector<bool>> location = {{true}};
    graph->loadLocation(location);

    std::shared_ptr<CharacterStatsInstance> stats = std::make_shared<CharacterStatsInstance>();
    stats->setMoveSpeed(10);

    Character character(1, graph, stats);
    character.spawn(Point(0, 0));

    std::shared_ptr<BuffInstance> buffSlowDown = std::make_shared<BuffInstance>();
    buffSlowDown->setMoveSpeedModifier(0.9);

    character.addBuff(buffSlowDown);
    EXPECT_EQ(character.getCurrentStats().getMoveSpeed(), 9);

    character.removeBuff(buffSlowDown);
    EXPECT_EQ(character.getCurrentStats().getMoveSpeed(), 10);

    // Multiple buffs
    character.addBuff(buffSlowDown);
    character.addBuff(buffSlowDown);
    character.addBuff(buffSlowDown);
    character.addBuff(buffSlowDown);
    EXPECT_EQ(character.getCurrentStats().getMoveSpeed(), 6);

    character.removeBuff(buffSlowDown);
    EXPECT_EQ(character.getCurrentStats().getMoveSpeed(), 7);
}
