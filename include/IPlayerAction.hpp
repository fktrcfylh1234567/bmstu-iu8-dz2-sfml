//
// Created by fktrc on 18.04.19.
//

#ifndef GAME_IPLAYERACTION_HPP
#define GAME_IPLAYERACTION_HPP

class IPlayerAction {
public:
    virtual size_t getActionId() = 0;
    virtual size_t getPlayerId() = 0;

    enum {
        ActionIdMove = 2,
        ActionIdAttack = 3
    };
};

#endif //GAME_IPLAYERACTION_HPP
