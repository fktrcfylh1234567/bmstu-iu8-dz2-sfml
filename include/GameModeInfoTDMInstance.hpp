//
// Created by fktrc on 28.04.19.
//

#ifndef GAME_GAMEMODEINFOTDMINSTANCE_HPP
#define GAME_GAMEMODEINFOTDMINSTANCE_HPP

#include <IGameModeInfoTDM.hpp>

class GameModeInfoTDMInstance : public IGameModeInfoTDM {
public:
    const std::vector<Point> getTeamSpawnPoints(size_t teamId) const override {
        return teamsSpawnPoints.at(teamId);
    }

    void addTeamSpawnPoints(size_t teamId, const std::vector<Point>& teamSpawnPoints) {
        teamsSpawnPoints.emplace(teamId, teamSpawnPoints);
    }

private:
    std::map<size_t, std::vector<Point>> teamsSpawnPoints;
};

#endif //GAME_GAMEMODEINFOTDMINSTANCE_HPP
