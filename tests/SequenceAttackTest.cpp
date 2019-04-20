//
// Created by fktrc on 20.04.19.
//

//
// Created by fktrc on 19.04.19.
//

#include <gtest/gtest.h>

#include <GameInstance.hpp>
#include <LocationInstance.hpp>

TEST(SequencesTest, SequenceAttackNear) {
    std::vector<std::vector<bool>> location = {{true, true, true},
                                               {true, true, true},
                                               {true, true, true}};
    std::shared_ptr<ILocation> ilocation = std::make_shared<LocationInstance>(location);

    std::shared_ptr<CharacterStatsInstance> stats = std::make_shared<CharacterStatsInstance>();
    stats->setMoveSpeed(1);

    stats->setHp(1000);
    stats->setAttackSpeed(2);
    stats->setAttackRange(1);
    stats->setAttackDamage(500);

    GameInstance gameInstance(3);
    gameInstance.loadLocation(ilocation);
    gameInstance.addGameRules(1);

    size_t id1 = gameInstance.addCharacter(stats);
    gameInstance.update(1);

    gameInstance.addMoveSequence(id1, Point(1, 1));
    gameInstance.update(2);

    size_t id2 = gameInstance.addCharacter(stats);
    gameInstance.update(3);

    gameInstance.addAttackSequence(id1, id2);
    gameInstance.update(4);
    EXPECT_EQ(gameInstance.getCharacters().at(id2).getCurrentStats().getHp(), 500);

    gameInstance.update(6);
    EXPECT_FALSE(gameInstance.getCharacters().at(id2).isAlive());
}

TEST(SequencesTest, SequenceAttackDistance) {
    std::vector<std::vector<bool>> location = {{true, true, true},
                                               {true, true, true},
                                               {true, true, true}};
    std::shared_ptr<ILocation> ilocation = std::make_shared<LocationInstance>(location);

    std::shared_ptr<CharacterStatsInstance> stats = std::make_shared<CharacterStatsInstance>();
    stats->setMoveSpeed(1);

    stats->setHp(1000);
    stats->setAttackSpeed(1);
    stats->setAttackRange(3);
    stats->setAttackDamage(500);

    GameInstance gameInstance(3);
    gameInstance.loadLocation(ilocation);
    gameInstance.addGameRules(1);

    size_t id1 = gameInstance.addCharacter(stats);
    gameInstance.update(1);

    gameInstance.addMoveSequence(id1, Point(1, 2));
    gameInstance.update(2);
    gameInstance.update(3);
    gameInstance.update(4);

    size_t id2 = gameInstance.addCharacter(stats);
    gameInstance.update(5);

    gameInstance.addAttackSequence(id1, id2);
    gameInstance.update(6);
    EXPECT_EQ(gameInstance.getCharacters().at(id2).getCurrentStats().getHp(), 500);

    gameInstance.update(7);
    EXPECT_FALSE(gameInstance.getCharacters().at(id2).isAlive());
}

TEST(SequencesTest, SequenceAttackMove) {
    std::vector<std::vector<bool>> location = {{true, true, true},
                                               {true, true, true},
                                               {true, true, true}};
    std::shared_ptr<ILocation> ilocation = std::make_shared<LocationInstance>(location);

    std::shared_ptr<CharacterStatsInstance> stats = std::make_shared<CharacterStatsInstance>();
    stats->setMoveSpeed(1);

    stats->setHp(1000);
    stats->setAttackSpeed(1);
    stats->setAttackRange(1);
    stats->setAttackDamage(500);

    GameInstance gameInstance(3);
    gameInstance.loadLocation(ilocation);
    gameInstance.addGameRules(1);

    size_t id1 = gameInstance.addCharacter(stats);
    gameInstance.update(1);

    gameInstance.addMoveSequence(id1, Point(0, 2));
    gameInstance.update(2);
    gameInstance.update(3);

    size_t id2 = gameInstance.addCharacter(stats);
    gameInstance.update(4);

    gameInstance.addAttackSequence(id1, id2);
    gameInstance.update(5);
    gameInstance.update(6);
    EXPECT_EQ(gameInstance.getCharacters().at(id2).getCurrentStats().getHp(), 500);
}

TEST(SequencesTest, SequenceAttackFollow) {
    std::vector <std::vector<bool>> location = {{true, true, true},
                                                {true, true, true},
                                                {true, true, true}};
    std::shared_ptr <ILocation> ilocation = std::make_shared<LocationInstance>(location);

    std::shared_ptr <CharacterStatsInstance> stats = std::make_shared<CharacterStatsInstance>();
    stats->setMoveSpeed(1);

    stats->setHp(1000);
    stats->setAttackSpeed(1);
    stats->setAttackRange(1);
    stats->setAttackDamage(500);

    GameInstance gameInstance(3);
    gameInstance.loadLocation(ilocation);
    gameInstance.addGameRules(1);

    size_t id1 = gameInstance.addCharacter(stats);
    gameInstance.update(1);

    gameInstance.addMoveSequence(id1, Point(0, 2));
    gameInstance.update(2);
    gameInstance.update(3);

    size_t id2 = gameInstance.addCharacter(stats);
    gameInstance.update(4);

    gameInstance.addAttackSequence(id2, id1);
    gameInstance.addMoveSequence(id1, Point(2, 2));

    for (size_t i = 5; i < 10; i++) {
        gameInstance.update(i);
    }
    EXPECT_EQ(gameInstance.getCharacters().at(id1).getCurrentStats().getHp(), 0);
}
