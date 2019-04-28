//
// Created by fktrc on 27.04.19.
//

#include <gtest/gtest.h>

#include <GameInstance.hpp>
#include <LocationInstance.hpp>

TEST(InstanceTest, Characters) {
    std::vector<std::vector<bool>> location = {{true}};
    std::shared_ptr<ILocation> ilocation = std::make_shared<LocationInstance>(location);

    std::shared_ptr<CharacterStatsInstance> stats = std::make_shared<CharacterStatsInstance>();
    stats->setHp(1000);
    stats->setMoveSpeed(10);

    GameInstance gameInstance(1);
    gameInstance.loadLevel(ilocation);
    gameInstance.addGameRules(1);
    size_t id = gameInstance.addCharacter(stats, 0);
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

TEST(InstanceTest, EventAdd) {
    GameInstance gameInstance(1);
    gameInstance.addGameEvent(GAME_EVENT_ENTITY_IS_ALIVE_CHANGED, 1, 1);
    EXPECT_EQ(gameInstance.getGameInstanceUpdates().size(), 1);

    auto value = gameInstance.getGameInstanceUpdates().front();
    EXPECT_EQ(value->getActionId(), GAME_EVENT_ENTITY_IS_ALIVE_CHANGED);
}
