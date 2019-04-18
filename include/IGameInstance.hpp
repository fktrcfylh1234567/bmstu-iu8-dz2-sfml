//
// Created by fktrc on 11.04.19.
//

#ifndef GAME_IGAMEINSTANCE_HPP
#define GAME_IGAMEINSTANCE_HPP

#include "ICharacterStats.hpp"

typedef std::pair<size_t, size_t> Point;

class IGameInstance {
public:
    virtual void update(size_t currentTime) = 0;

    virtual size_t spawnCharacter(std::shared_ptr<ICharacterStats> characterStats) = 0;
    virtual void removeCharacter(size_t characterId) = 0;

    virtual void addMoveSequence(size_t characterId, Point& point) = 0;
    virtual void addAttackSequence(size_t characterId, size_t targetId) = 0;
    virtual void removeCharacterActiveSequence(size_t characterId) = 0;
};

#endif //GAME_IGAMEINSTANCE_HPP
