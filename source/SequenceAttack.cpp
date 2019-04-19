//
// Created by fktrc on 18.04.19.
//

#include "SequenceAttack.hpp"


SequenceAttack::SequenceAttack(size_t characterId, size_t targetId, size_t nextUpdateTime,
                               ILevelInstance* levelInstance) : characterId(characterId), targetId(targetId),
                                                                nextUpdateTime(nextUpdateTime),
                                                                levelInstance(levelInstance) {}

void SequenceAttack::Update() {

}

void SequenceAttack::Cancel() {
    canceled = true;
}

bool SequenceAttack::isCanceled() {
    return canceled;
}

size_t SequenceAttack::getNextUpdateTime() {
    return nextUpdateTime;
}

size_t SequenceAttack::getCharacterId() {
    return characterId;
}
