//
// Created by fktrc on 22.05.19.
//

#ifndef GAME_LEVEL_1_HPP
#define GAME_LEVEL_1_HPP


#include <LocationInstance.hpp>
#include <GameModeInfoTDMInstance.hpp>

class level_1 : public ILevel {
public:
    level_1() {
        std::vector<std::vector<bool>> enveronment =
                {
                        {true, true, true, true, true},
                        {true, true, true, true, true},
                        {true, true, false, false, true},
                        {true, true, false, true, true},
                        {true, true, true, true, true}
                };

        location = std::make_shared<LocationInstance>(enveronment);

        std::vector<Point> points1 = {Point(0, 0), Point(1, 0)};
        std::vector<Point> points2 = {Point(4, 4), Point(4, 3)};

        std::shared_ptr<GameModeInfoTDMInstance> tdmInfo = std::make_shared<GameModeInfoTDMInstance>();
        tdmInfo->addTeamSpawnPoints(1, points1);
        tdmInfo->addTeamSpawnPoints(2, points2);

        gameModesInfo.emplace(1, tdmInfo);
    }

    const std::shared_ptr<ILocation>& getLocation() override {
        return location;
    }

    std::shared_ptr<IGameModeInfo> getGameModeInfo(size_t gameModeId) override {
        return gameModesInfo.at(gameModeId);
    }

private:
    std::shared_ptr<ILocation> location;
    std::map<size_t, std::shared_ptr<IGameModeInfo>> gameModesInfo;
};

#endif //GAME_LEVEL_1_HPP
