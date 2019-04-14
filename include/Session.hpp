//
// Created by fktrc on 11.04.19.
//

#ifndef GAME_SESSION_HPP
#define GAME_SESSION_HPP

#include <UserAction.hpp>

class Session {
    virtual void run() = 0;
    virtual void stop() = 0;
    virtual void handleAction(UserAction action) = 0;
};

#endif //GAME_SESSION_HPP
