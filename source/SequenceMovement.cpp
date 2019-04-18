//
// Created by fktrc on 18.04.19.
//

#include "SequenceMovement.hpp"

SequenceMovement::SequenceMovement(size_t characterId, Point& point, ILevelInstance* actionSpace) : characterId(
        characterId), point(point), actionSpace(actionSpace) {}

void SequenceMovement::Update() {

}

void SequenceMovement::Cancel() {

}

bool SequenceMovement::isCanceled() {
    return false;
}

size_t SequenceMovement::getNextUpdateTime() {
    return 0;
}
