//
// Created by fktrc on 19.04.19.
//

#include <gtest/gtest.h>
#include <algorithm>

#include <GameInstance.hpp>
#include <LocationInstance.hpp>

TEST(SequencesTest, Characters) {
    std::vector<std::vector<bool>> location = {{true}};
    std::shared_ptr<ILocation> ilocation = std::make_shared<LocationInstance>(location);

    std::shared_ptr<CharacterStatsInstance> stats = std::make_shared<CharacterStatsInstance>();
    stats->setHp(1000);
    stats->setMoveSpeed(10);

    GameInstance gameInstance(1);
    gameInstance.loadLocation(ilocation);
    gameInstance.addGameRules(1);
    size_t id = gameInstance.addCharacter(stats);
    gameInstance.update(1);
    EXPECT_EQ(id, 1);
    EXPECT_EQ(gameInstance.getCharacters().size(), 1);
    EXPECT_EQ(gameInstance.getCharacters().at(id).isAlive(), true);
    EXPECT_EQ(gameInstance.getGraph()->isFree(0, 0), false);
    EXPECT_EQ(gameInstance.getCharacters().at(id).getCurrentStats().getHp(), 1000);

    gameInstance.getCharacters().at(id).doDamage(250);
    EXPECT_EQ(gameInstance.getCharacters().at(id).getCurrentStats().getHp(), 750);

    gameInstance.update(2);
    gameInstance.getCharacters().at(id).doDamage(800);
    EXPECT_EQ(gameInstance.getCharacters().at(id).getCurrentStats().getHp(), 0);
    EXPECT_EQ(gameInstance.getCharacters().at(id).isAlive(), false);

    gameInstance.update(3);
    EXPECT_EQ(gameInstance.getCharacters().at(id).isAlive(), true);
    EXPECT_EQ(gameInstance.getCharacters().at(id).getCurrentStats().getHp(), 1000);
}

TEST(SequencesTest, SequenceMovement) {
    std::vector<std::vector<bool>> location = {{true, true, true},
                                               {true, true, true},
                                               {true, true, true}};
    std::shared_ptr<ILocation> ilocation = std::make_shared<LocationInstance>(location);

    std::shared_ptr<CharacterStatsInstance> stats = std::make_shared<CharacterStatsInstance>();
    stats->setHp(1000);
    stats->setMoveSpeed(1);

    GameInstance gameInstance(3);
    gameInstance.loadLocation(ilocation);
    gameInstance.addGameRules(1);

    size_t id = gameInstance.addCharacter(stats);
    gameInstance.update(1);

    gameInstance.addMoveSequence(id, Point(2, 2));
    gameInstance.update(2);
    gameInstance.getGraph()->busyPoint(Point(1, 1));

    for (size_t i = 2; i < 7; i++) {
        gameInstance.update(i);
    }

    EXPECT_EQ(gameInstance.getCharacters().at(id).getPos(), Point(2, 2));

    gameInstance.addMoveSequence(id, Point(2, 2));
    gameInstance.update(7);
    EXPECT_EQ(gameInstance.getCharacters().at(id).getPos(), Point(2, 2));
}

TEST(SequencesTest, SequenceMovementTwoCharacters) {
    std::vector<std::vector<bool>> location = {{true, true, true},
                                               {true, true, true},
                                               {true, true, true}};
    std::shared_ptr<ILocation> ilocation = std::make_shared<LocationInstance>(location);

    std::shared_ptr<CharacterStatsInstance> stats = std::make_shared<CharacterStatsInstance>();
    stats->setHp(1000);
    stats->setMoveSpeed(1);

    GameInstance gameInstance(3);
    gameInstance.loadLocation(ilocation);
    gameInstance.addGameRules(1);

    size_t id1 = gameInstance.addCharacter(stats);
    gameInstance.update(1);

    gameInstance.addMoveSequence(id1, Point(0, 2));
    gameInstance.update(2);
    gameInstance.update(3);
    EXPECT_EQ(gameInstance.getCharacters().at(id1).getPos(), Point(0, 2));

    size_t id2 = gameInstance.addCharacter(stats);
    gameInstance.update(4);

    gameInstance.addMoveSequence(id1, Point(2, 1));
    gameInstance.addMoveSequence(id2, Point(2, 2));
    for (size_t i = 5; i < 11; i++) {
        gameInstance.update(i);
    }

    EXPECT_EQ(gameInstance.getCharacters().at(id1).getPos(), Point(2, 1));
    EXPECT_EQ(gameInstance.getCharacters().at(id2).getPos(), Point(2, 2));
}