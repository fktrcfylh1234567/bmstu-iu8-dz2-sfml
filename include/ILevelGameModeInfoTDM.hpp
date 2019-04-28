//
// Created by fktrc on 28.04.19.
//

#ifndef GAME_ILEVELGAMEMODEINFOTDM_HPP
#define GAME_ILEVELGAMEMODEINFOTDM_HPP

#include <map>
#include <vector>

#include <ILevelGameModeInfo.hpp>

typedef std::pair<size_t, size_t> Point;

class ILevelGameModeInfoTDM : public ILevelGameModeInfo {
public:
    virtual const std::map<size_t, std::vector<Point>> getTeamsSpawnPoints() const = 0;
};

#endif //GAME_ILEVELGAMEMODEINFOTDM_HPP
