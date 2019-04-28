//
// Created by fktrc on 11.04.19.
//

#ifndef GAME_IGAMEINSTANCE_HPP
#define GAME_IGAMEINSTANCE_HPP

#include "ICharacterStats.hpp"
#include "ILocation.hpp"
#include "GameEventEntityInstance.hpp"
#include "ILevel.hpp"

typedef std::pair<size_t, size_t> Point;

class IGameInstance {
public:
    virtual void loadLevel(std::shared_ptr<ILevel> level) = 0;
    virtual void addGameRules(size_t gameModeId) = 0;
    virtual void update(size_t currentTime) = 0;
    virtual std::queue<std::shared_ptr<IGameEvent>>& getGameInstanceUpdates() = 0;

    virtual size_t addCharacter(std::shared_ptr<ICharacterStats> characterStats, size_t teamId) = 0;
    virtual void removeCharacter(size_t characterId) = 0;

    virtual void addMoveSequence(size_t characterId, const Point& point) = 0;
    virtual void addAttackSequence(size_t characterId, size_t targetId) = 0;
    virtual void cancelCharacterActiveSequences(size_t characterId) = 0;
};

#endif //GAME_IGAMEINSTANCE_HPP
