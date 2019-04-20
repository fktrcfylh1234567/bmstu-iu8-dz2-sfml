//
// Created by fktrc on 18.04.19.
//

#ifndef GAME_SEQUENCECHARACTERATTACK_HPP
#define GAME_SEQUENCECHARACTERATTACK_HPP

#include <algorithm>
#include <cmath>

#include "ISequenceCharacter.hpp"
#include "ILevelInstance.hpp"

class SequenceCharacterAttack : public ISequenceCharacter {
public:
    SequenceCharacterAttack(size_t characterId, size_t targetId, size_t nextUpdateTime, ILevelInstance* levelInstance);

    void Update() override;
    void Cancel() override;
    bool isCanceled() override;
    size_t getNextUpdateTime() override;
    size_t getCharacterId() override;

private:
    bool canceled = false;
    size_t characterId = 0;
    size_t targetId = 0;
    size_t nextUpdateTime = 0;
    ILevelInstance* levelInstance = nullptr;
    Path path;

    void updatePath();
    bool canReach();
    bool isPathActual();
    bool isPathValid();
    void makePath();
};

#endif //GAME_SEQUENCECHARACTERATTACK_HPP
