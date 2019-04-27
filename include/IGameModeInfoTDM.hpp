//
// Created by fktrc on 27.04.19.
//

#ifndef GAME_IGAMEMODEINFOTDM_HPP
#define GAME_IGAMEMODEINFOTDM_HPP

enum gameModeTDM {
    GAME_MODE_TDM = 0
};

typedef std::pair<size_t, size_t> Point;

class IGameModeInfoTDM : public IGameModeInfo {
public:
    virtual const size_t getGameModeId() const override = 0;
    virtual const std::vector<Point>& getFirstTeamSpawnPoints() const = 0;
    virtual const std::vector<Point>& getSecondTeamSpawnPoints() const = 0;
};

#endif //GAME_IGAMEMODEINFOTDM_HPP
