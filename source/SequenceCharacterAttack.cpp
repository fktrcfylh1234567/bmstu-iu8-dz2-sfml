//
// Created by fktrc on 18.04.19.
//

#include "SequenceCharacterAttack.hpp"

SequenceCharacterAttack::SequenceCharacterAttack(size_t characterId, size_t targetId, size_t nextUpdateTime,
                                                 IGameInstance* levelInstance) : characterId(characterId),
                                                                                  targetId(targetId),
                                                                                  nextUpdateTime(nextUpdateTime),
                                                                                  gameInstance(levelInstance) {}

void SequenceCharacterAttack::Update() {
    if (!gameInstance->getCharacters().at(characterId).isAlive()) {
        Cancel();
        return;
    }

    if (!gameInstance->getCharacters().at(targetId).isAlive()) {
        Cancel();
        return;
    }

    if (canReach()) {
        gameInstance->getCharacters().at(targetId).doDamage(
                gameInstance->getCharacters().at(characterId).getCurrentStats().getAttackDamage());
        gameInstance->addGameEvent(GAME_EVENT_ENTITY_HP_CHANGED, characterId,
                                    gameInstance->getCharacters().at(targetId).getCurrentStats().getHp());

        if (!gameInstance->getCharacters().at(targetId).isAlive()) {
            gameInstance->addGameEvent(GAME_EVENT_ENTITY_IS_ALIVE_CHANGED, characterId, 0);
            Cancel();
            return;
        }

        nextUpdateTime += gameInstance->getCharacters().at(characterId).getCurrentStats().getAttackSpeed();
        return;
    }

    updatePath();
    path.erase(path.begin());
    gameInstance->getCharacters().at(characterId).setPosition(path[0]);
    gameInstance->addGameEvent(GAME_EVENT_ENTITY_POSITION_CHANGED, characterId, pointToIndex(path[0]));

    nextUpdateTime += gameInstance->getCharacters().at(characterId).getCurrentStats().getMoveSpeed();
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
    size_t range = gameInstance->getCharacters().at(characterId).getCurrentStats().getAttackRange();
    Point attackerPos = gameInstance->getCharacters().at(characterId).getPos();
    Point targetPos = gameInstance->getCharacters().at(targetId).getPos();
    return sqrt(pow((int) attackerPos.first - (int) targetPos.first, 2) +
                pow((int) attackerPos.second - (int) targetPos.second, 2)) < range + 1;
}

bool SequenceCharacterAttack::isPathActual() {
    return path[path.size() - 1] == gameInstance->getCharacters().at(targetId).getPos();
}

bool SequenceCharacterAttack::isPathValid() {
    return std::all_of(path.begin(), path.end(), [this](const Point& point) {
        return gameInstance->getGraph()->isFree(point);
    });
}

void SequenceCharacterAttack::makePath() {
    gameInstance->getGraph()->releasePoint(gameInstance->getCharacters().at(targetId).getPos());
    path = gameInstance->getCharacters().at(characterId).makePath(
            gameInstance->getCharacters().at(targetId).getPos());
    gameInstance->getGraph()->busyPoint(gameInstance->getCharacters().at(targetId).getPos());
}

size_t SequenceCharacterAttack::pointToIndex(const Point& point) {
    return gameInstance->getLocationSize() * point.first + point.second;
}

size_t SequenceCharacterAttack::getSequenceID() {
    return 3;
}
