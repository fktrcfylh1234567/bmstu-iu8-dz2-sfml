//
// Created by fktrc on 27.04.19.
//

#ifndef GAME_GAMEMODEINFOTDMINSTANCE_HPP
#define GAME_GAMEMODEINFOTDMINSTANCE_HPP

#include <IGameModeInfoTDM.hpp>

class GameModeInfoTDMInstance : public IGameModeInfoTDM {
public:
    const size_t getGameModeId() const override {
        return GAME_MODE_TDM;
    }

    const std::vector<Point>& getFirstTeamSpawnPoints() const {
        return firstTeamSpawnPoints;
    }

    const std::vector<Point>& getSecondTeamSpawnPoints() const {
        return secondTeamSpawnPoints;
    }

    void setFirstTeamSpawnPoints(const std::vector<Point>& firstTeamSpawnPoints) {
        GameModeInfoTDMInstance::firstTeamSpawnPoints = firstTeamSpawnPoints;
    }

    void setSecondTeamSpawnPoints(const std::vector<Point>& secondTeamSpawnPoints) {
        GameModeInfoTDMInstance::secondTeamSpawnPoints = secondTeamSpawnPoints;
    }

private:
    std::vector<Point> firstTeamSpawnPoints;
    std::vector<Point> secondTeamSpawnPoints;
};

#endif //GAME_GAMEMODEINFOTDMINSTANCE_HPP
