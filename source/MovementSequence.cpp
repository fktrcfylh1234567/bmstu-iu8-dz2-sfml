//
// Created by fktrc on 18.04.19.
//

#include "MovementSequence.hpp"

MovementSequence::MovementSequence(size_t characterId, Point& point, ActionSpace* actionSpace) : characterId(
        characterId), point(point), actionSpace(actionSpace) {}

void MovementSequence::Update() {

}

void MovementSequence::Cancel() {

}

bool MovementSequence::isCanceled() {
    return false;
}

size_t MovementSequence::getNextUpdateTime() {
    return 0;
}
