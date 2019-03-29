//
// Created by fktrc on 25.03.19.
//

#include <Entity.hpp>

Entity::Entity(GameGraph* gameGraph) {
    this->gameGraph = gameGraph;
}

void Entity::spawn(const Point& pos) {
    if (!this->gameGraph->isFree(pos)) {
        return;
    }

    alive = true;
    this->pos = pos;
    gameGraph->busyPoint(this->pos);
}

void Entity::destroy() {
    alive = false;
    gameGraph->releasePoint(this->pos);
}

void Entity::setPosition(const Point& pos) {
    if (!this->gameGraph->isFree(pos)) {
        return;
    }

    gameGraph->releasePoint(this->pos);
    this->pos = pos;
    gameGraph->busyPoint(this->pos);
}

bool Entity::isAlive() {
    return alive;
}

const Point& Entity::getPos() const {
    return pos;
}
