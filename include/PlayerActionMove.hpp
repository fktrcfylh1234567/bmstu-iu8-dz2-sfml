//
// Created by fktrc on 22.05.19.
//

#ifndef GAME_PLAYERACTIONMOVE_H
#define GAME_PLAYERACTIONMOVE_H

#include <IPlayerAction.hpp>

class PlayerActionMove : public IPlayerAction {
public:
    PlayerActionMove(size_t playerId, const Point& dest) : playerId(playerId), dest(dest) {}

    size_t getActionId() override {
        return ActionIdMove;
    }

    size_t getPlayerId() override {
        return playerId;
    }

    const Point& getDest() const {
        return dest;
    }

private:
    size_t playerId;
    Point dest;
};

#endif //GAME_PLAYERACTIONMOVE_H
