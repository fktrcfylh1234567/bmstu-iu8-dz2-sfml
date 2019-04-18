//
// Created by fktrc on 11.04.19.
//

#ifndef GAME_ISESSION_HPP
#define GAME_ISESSION_HPP

#include "IPlayerAction.hpp"

class ISession {
public:
    virtual void run() = 0;
    virtual void stop() = 0;
    virtual void handleAction(std::shared_ptr<IPlayerAction> action) = 0;
};

#endif //GAME_ISESSION_HPP
