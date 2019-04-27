//
// Created by fktrc on 20.04.19.
//

#include <gtest/gtest.h>

#include <GameInstance.hpp>
#include <LocationInstance.hpp>

TEST(SequenceMovementTest, SequenceMovement) {
    std::vector<std::vector<bool>> location = {{true, true, true},
                                               {true, true, true},
                                               {true, true, true}};
    std::shared_ptr<ILocation> ilocation = std::make_shared<LocationInstance>(location);

    std::shared_ptr<CharacterStatsInstance> stats = std::make_shared<CharacterStatsInstance>();
    stats->setHp(1000);
    stats->setMoveSpeed(1);

    GameInstance gameInstance(3);
    gameInstance.loadLevel(ilocation);
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

    auto value = gameInstance.getGameInstanceUpdates().back();
    EXPECT_EQ(value->getActionId(), GAME_EVENT_ENTITY_POSITION_CHANGED);
}

TEST(SequenceMovementTest, SequenceMovementTwoCharacters) {
    std::vector<std::vector<bool>> location = {{true, true, true},
                                               {true, true, true},
                                               {true, true, true}};
    std::shared_ptr<ILocation> ilocation = std::make_shared<LocationInstance>(location);

    std::shared_ptr<CharacterStatsInstance> stats = std::make_shared<CharacterStatsInstance>();
    stats->setHp(1000);
    stats->setMoveSpeed(1);

    GameInstance gameInstance(3);
    gameInstance.loadLevel(ilocation);
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
    for (size_t i = 5; i < 8; i++) {
        gameInstance.update(i);
    }

    EXPECT_EQ(gameInstance.getCharacters().at(id1).getPos(), Point(2, 1));
    EXPECT_EQ(gameInstance.getCharacters().at(id2).getPos(), Point(1, 0));

    for (size_t i = 8; i < 11; i++) {
        gameInstance.update(i);
    }

    EXPECT_EQ(gameInstance.getCharacters().at(id2).getPos(), Point(2, 2));
}

TEST(SequenceMovementTest, SequenceCancel) {
    std::vector<std::vector<bool>> location = {{true, true, true},
                                               {true, true, true},
                                               {true, true, true}};
    std::shared_ptr<ILocation> ilocation = std::make_shared<LocationInstance>(location);

    std::shared_ptr<CharacterStatsInstance> stats = std::make_shared<CharacterStatsInstance>();
    stats->setMoveSpeed(1);

    GameInstance gameInstance(3);
    gameInstance.loadLevel(ilocation);
    gameInstance.addGameRules(1);
    size_t id = gameInstance.addCharacter(stats);
    gameInstance.update(1);

    gameInstance.addMoveSequence(id, Point(2, 2));
    gameInstance.update(2);
    size_t id2 = gameInstance.addCharacter(stats);
    gameInstance.update(3);
    gameInstance.addMoveSequence(id2, Point(0, 2));

    gameInstance.cancelCharacterActiveSequences(id);
    gameInstance.update(4);
    gameInstance.cancelCharacterActiveSequences(id);

    EXPECT_EQ(gameInstance.getCharacters().at(id).getPos(), Point(2, 0));
    EXPECT_EQ(gameInstance.getCharacters().at(id2).getPos(), Point(0, 1));
}
