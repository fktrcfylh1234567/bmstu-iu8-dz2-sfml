//
// Created by fktrc on 18.04.19.
//

#include <SequenceCharacterMovement.hpp>
#include <EventEntityInstance.hpp>

SequenceCharacterMovement::SequenceCharacterMovement(size_t characterId, const Point& dest, size_t nextUpdateTime,
                                                     IGameInstance* levelInstance) :
        characterId(characterId), dest(dest), nextUpdateTime(nextUpdateTime), gameInstance(levelInstance) {}

size_t SequenceCharacterMovement::getSequenceID() {
    return 2;
}

void SequenceCharacterMovement::Update() {
    if (!gameInstance->getCharacters().at(characterId).isAlive()) {
        Cancel();
        return;
    }

    updatePath();
    path.erase(path.begin());
    gameInstance->getCharacters().at(characterId).setPosition(path[0]);
    gameInstance->addGameEvent(GAME_EVENT_ENTITY_POSITION_CHANGED, characterId, pointToIndex(path[0]));

    if (path.size() == 1) {
        Cancel();
        return;
    }

    nextUpdateTime += gameInstance->getCharacters().at(characterId).getCurrentStats().getMoveSpeed();
}

void SequenceCharacterMovement::Cancel() {
    canceled = true;
}

bool SequenceCharacterMovement::isCanceled() {
    return canceled;
}

size_t SequenceCharacterMovement::getNextUpdateTime() {
    return nextUpdateTime;
}

size_t SequenceCharacterMovement::getCharacterId() {
    return characterId;
}

void SequenceCharacterMovement::updatePath() {
    if (path.size() == 0) {
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

bool SequenceCharacterMovement::isPathValid() {
    return std::all_of(path.begin(), path.end(), [this](const Point& point) {
        return gameInstance->getGraph()->isFree(point);
    });
}

void SequenceCharacterMovement::makePath() {
    path = gameInstance->getCharacters().at(characterId).makePath(dest);
}

size_t SequenceCharacterMovement::pointToIndex(const Point& point) {
    return gameInstance->getLocationSize() * point.first + point.second;
}
