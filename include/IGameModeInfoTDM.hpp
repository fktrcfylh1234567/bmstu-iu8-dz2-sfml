//
// Created by fktrc on 28.04.19.
//

#ifndef GAME_IGAMEMODEINFOTDM_HPP
#define GAME_IGAMEMODEINFOTDM_HPP

#include <map>
#include <vector>

#include <IGameModeInfo.hpp>

typedef std::pair<size_t, size_t> Point;

class IGameModeInfoTDM : public IGameModeInfo {
public:
    virtual const std::vector<Point> getTeamSpawnPoints(size_t teamId) const = 0;
    size_t getGameModeId() const override {
        return 1;
    }
};

#endif //GAME_IGAMEMODEINFOTDM_HPP
