//
// Created by fktrc on 27.04.19.
//

#include <gtest/gtest.h>

#include <GameInstance.hpp>
#include <LocationInstance.hpp>
#include <GameModeInfoTDMInstance.hpp>
#include <LevelInstance.hpp>

TEST(InstanceTest, Level) {
    std::vector<std::vector<bool>> location = {{true, true, true},
                                               {true, true, true},
                                               {true, true, true}};
    std::shared_ptr<ILocation> ilocation = std::make_shared<LocationInstance>(location);

    std::vector<Point> points = {Point(2, 1)};
    std::shared_ptr<GameModeInfoTDMInstance> tdmInfo = std::make_shared<GameModeInfoTDMInstance>();
    tdmInfo->addTeamSpawnPoints(1, points);

    std::shared_ptr<LevelInstance> level = std::make_shared<LevelInstance>();
    level->setLocation(ilocation);
    level->addGameModeInfo(tdmInfo);

    std::shared_ptr<CharacterStatsInstance> stats = std::make_shared<CharacterStatsInstance>();
    stats->setHp(1000);
    stats->setMoveSpeed(10);

    GameInstance gameInstance(3);
    gameInstance.loadLevel(level);
    gameInstance.addGameRules(1);

    std::shared_ptr<IGameModeInfo> infoINST = gameInstance.getLevel()->getGameModeInfo(1);
    IGameModeInfoTDM* tdmInfoINST = dynamic_cast<IGameModeInfoTDM*>(infoINST.get());
    EXPECT_EQ(tdmInfoINST->getTeamSpawnPoints(1).at(0), Point(2, 1));
}

TEST(InstanceTest, Characters) {
    std::vector<std::vector<bool>> location = {{true, true, true},
                                               {true, true, true},
                                               {true, true, true}};
    std::shared_ptr<ILocation> ilocation = std::make_shared<LocationInstance>(location);

    std::vector<Point> points;
    points.push_back({2, 2});

    std::shared_ptr<GameModeInfoTDMInstance> tdmInfo = std::make_shared<GameModeInfoTDMInstance>();
    tdmInfo->addTeamSpawnPoints(1, points);

    std::shared_ptr<LevelInstance> level = std::make_shared<LevelInstance>();
    level->setLocation(ilocation);
    level->addGameModeInfo(tdmInfo);

    std::shared_ptr<CharacterStatsInstance> stats = std::make_shared<CharacterStatsInstance>();
    stats->setHp(1000);
    stats->setMoveSpeed(10);

    GameInstance gameInstance(3);
    gameInstance.loadLevel(level);
    gameInstance.addGameRules(1);
    size_t id = gameInstance.addCharacter(stats, 1);

    gameInstance.update(1);
    EXPECT_EQ(id, 1);
    EXPECT_EQ(gameInstance.getCharacters().size(), 1);
    EXPECT_EQ(gameInstance.getCharacters().at(id).isAlive(), true);
    EXPECT_EQ(gameInstance.getCharacters().at(id).getPos(), Point(2, 2));
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
