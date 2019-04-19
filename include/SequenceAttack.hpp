//
// Created by fktrc on 18.04.19.
//

#ifndef GAME_SEQUENCEATTACK_HPP
#define GAME_SEQUENCEATTACK_HPP

#include "ISequenceCharacter.hpp"
#include "ILevelInstance.hpp"

class SequenceAttack : public ISequenceCharacter {
public:
    SequenceAttack(size_t characterId, size_t targetId, size_t nextUpdateTime, ILevelInstance* levelInstance);

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
};

#endif //GAME_SEQUENCEATTACK_HPP
