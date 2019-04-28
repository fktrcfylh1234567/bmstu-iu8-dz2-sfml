//
// Created by fktrc on 28.04.19.
//

#ifndef GAME_LEVELGAMEMODEINFOTDMINSTANCE_HPP
#define GAME_LEVELGAMEMODEINFOTDMINSTANCE_HPP

#include <ILevelGameModeInfoTDM.hpp>

class LevelGameModeInfoTDMInstance : public ILevelGameModeInfoTDM {
public:
    const std::map<size_t, std::vector<Point>> getTeamsSpawnPoints() const override {
        return teamsSpawnPoints;
    }

    void addTeamsSpawnPoints(size_t teamId, const std::vector<Point>& teamSpawnPoints) {
        teamsSpawnPoints.emplace(teamId, teamSpawnPoints);
    }

private:
    std::map<size_t, std::vector<Point>> teamsSpawnPoints;
};


#endif //GAME_LEVELGAMEMODEINFOTDMINSTANCE_HPP
