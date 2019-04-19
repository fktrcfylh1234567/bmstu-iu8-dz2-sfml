//
// Created by fktrc on 18.04.19.
//

#include <algorithm>
#include "SequenceMovement.hpp"

SequenceMovement::SequenceMovement(size_t characterId, const Point& dest, size_t nextUpdateTime,
                                   ILevelInstance* levelInstance) : characterId(characterId), dest(dest),
                                                                    nextUpdateTime(nextUpdateTime),
                                                                    levelInstance(levelInstance) {}

void SequenceMovement::Update() {
    if (path.size() == 0 || !isPathValid()) {
        path = levelInstance->getCharacters().at(characterId).makePath(dest);
        if (path.size() == 0) {
            Cancel();
            return;
        }
    }

    path.erase(path.begin());
    levelInstance->getCharacters().at(characterId).setPosition(path[0]);

    if (path.size() == 1) {
        Cancel();
        return;
    }

    nextUpdateTime += levelInstance->getCharacters().at(characterId).getCurrentStats().getMoveSpeed();
}

bool SequenceMovement::isPathValid() {
    return std::all_of(path.begin(), path.end(), [this](const Point& point) {
        return levelInstance->getGraph()->isFree(point);
    });
}

void SequenceMovement::Cancel() {
    canceled = true;
}

bool SequenceMovement::isCanceled() {
    return canceled;
}

size_t SequenceMovement::getNextUpdateTime() {
    return nextUpdateTime;
}

size_t SequenceMovement::getCharacterId() {
    return characterId;
}
