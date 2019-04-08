//
// Created by fktrc on 08.04.19.
//

#include "MovementSequence.hpp"

MovementSequence::MovementSequence(const size_t id, size_t nextUpdateTimeMs, Actor* actor, Graph* graph, Point dest)
        : Sequence(id, nextUpdateTimeMs) {
    this->actor = actor;
    this->graph = graph;
    this->dest = dest;

    path = this->actor->makePath(dest);
}

void MovementSequence::Update() {
    if (!actor->isAlive()) {
        return;
    }

    if (!isPathCorrect()) {
        path = this->actor->makePath(dest);
        return;
    }

    for (size_t i = 0; i < path.size(); i++) {
        if (path[i] == actor->getPos()) {
            actor->setPosition(path[i + 1]);
            break;
        }
    }

    this->nextUpdateTimeMs += actor->getMoveSpeed();
}

bool MovementSequence::isPathCorrect() {
    for (Point& point : path) {
        if (!graph->isFree(point)) {
            return false;
        }
    }
    return true;
}
