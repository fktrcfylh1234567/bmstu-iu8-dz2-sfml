//
// Created by fktrc on 11.04.19.
//

#ifndef GAME_IMATCH_HPP
#define GAME_IMATCH_HPP

#include "IPlayerAction.hpp"

class IMatch {
public:
    virtual void setupGame(std::string levelName, size_t gameModeId) = 0;
    virtual void addPlayer(size_t playerId, size_t charStatsId) = 0;

    virtual void run() = 0;
    virtual void stop() = 0;
    virtual bool isRunning() = 0;

    virtual void handleAction(std::shared_ptr<IPlayerAction> action) = 0;
};

#endif //GAME_IMATCH_HPP
