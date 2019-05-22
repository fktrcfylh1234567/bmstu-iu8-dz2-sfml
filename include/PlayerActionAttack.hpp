//
// Created by fktrc on 22.05.19.
//

#ifndef GAME_PLAYERACTIONATTACK_HPP
#define GAME_PLAYERACTIONATTACK_HPP

class PlayerActionAttack : public IPlayerAction {
public:
    PlayerActionAttack(size_t playersId, size_t targetId) : playerId(playersId), targetId(targetId) {}

    size_t getActionId() override {
        return ActionIdAttack;
    }

    size_t getPlayerId() override {
        return playerId;
    }

    size_t getTargetId() const {
        return targetId;
    }

private:
    size_t playerId;
    size_t targetId;
};

#endif //GAME_PLAYERACTIONATTACK_HPP
