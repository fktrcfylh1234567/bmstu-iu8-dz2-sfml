//
// Created by fktrc on 18.04.19.
//

#include "SequenceCharacterAttack.hpp"

SequenceCharacterAttack::SequenceCharacterAttack(size_t characterId, size_t targetId, size_t nextUpdateTime,
                                                 ILevelInstance* levelInstance) : characterId(characterId),
                                                                                  targetId(targetId),
                                                                                  nextUpdateTime(nextUpdateTime),
                                                                                  levelInstance(levelInstance) {}

void SequenceCharacterAttack::Update() {
    if (!levelInstance->getCharacters().at(characterId).isAlive()) {
        Cancel();
        return;
    }

    if (!levelInstance->getCharacters().at(targetId).isAlive()) {
        Cancel();
        return;
    }

    if (canReach()) {
        levelInstance->getCharacters().at(targetId).doDamage(
                levelInstance->getCharacters().at(characterId).getCurrentStats().getAttackDamage());
        if (!levelInstance->getCharacters().at(targetId).isAlive()) {
            Cancel();
            return;
        }
        nextUpdateTime += levelInstance->getCharacters().at(characterId).getCurrentStats().getAttackSpeed();
        return;
    }

    updatePath();
    path.erase(path.begin());
    levelInstance->getCharacters().at(characterId).setPosition(path[0]);

    nextUpdateTime += levelInstance->getCharacters().at(characterId).getCurrentStats().getMoveSpeed();
}

void SequenceCharacterAttack::Cancel() {
    canceled = true;
}

bool SequenceCharacterAttack::isCanceled() {
    return canceled;
}

size_t SequenceCharacterAttack::getNextUpdateTime() {
    return nextUpdateTime;
}

size_t SequenceCharacterAttack::getCharacterId() {
    return characterId;
}


void SequenceCharacterAttack::updatePath() {
    if (path.size() == 0) {
        makePath();
        if (path.size() == 0) {
            Cancel();
        }
        return;
    }

    if (!isPathActual()) {
        makePath();
        if (path.size() == 0) {
            Cancel();
        }
        return;
    }

    if (!isPathValid()) {
        makePath();
        if (path.size() == 0) {
            Cancel();
        }
    }
}

bool SequenceCharacterAttack::canReach() {
    size_t range = levelInstance->getCharacters().at(characterId).getCurrentStats().getAttackRange();
    Point attackerPos = levelInstance->getCharacters().at(characterId).getPos();
    Point targetPos = levelInstance->getCharacters().at(targetId).getPos();
    return sqrt(pow((int) attackerPos.first - (int) targetPos.first, 2) +
                pow((int) attackerPos.second - (int) targetPos.second, 2)) < range + 1;
}

bool SequenceCharacterAttack::isPathActual() {
    return path[path.size() - 1] == levelInstance->getCharacters().at(targetId).getPos();
}

bool SequenceCharacterAttack::isPathValid() {
    return std::all_of(path.begin(), path.end(), [this](const Point& point) {
        return levelInstance->getGraph()->isFree(point);
    });
}

void SequenceCharacterAttack::makePath() {
    levelInstance->getGraph()->releasePoint(levelInstance->getCharacters().at(targetId).getPos());
    path = levelInstance->getCharacters().at(characterId).makePath(
            levelInstance->getCharacters().at(targetId).getPos());
    levelInstance->getGraph()->busyPoint(levelInstance->getCharacters().at(targetId).getPos());
}
