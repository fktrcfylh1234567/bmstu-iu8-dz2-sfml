//
// Created by fktrc on 25.03.19.
//

#include <Entity.hpp>

Entity::Entity(GameGraph* gameGraph) {
    this->gameGraph = gameGraph;
}

void Entity::spawn(const Point& destination) {
    if (!this->gameGraph->isFree(destination)) {
        return;
    }

    alive = true;
    this->pos = destination;
    gameGraph->busyPoint(this->pos);
}

void Entity::destroy() {
    alive = false;
    gameGraph->releasePoint(this->pos);
}

void Entity::setPosition(const Point& destination) {
    if (!this->gameGraph->isFree(destination)) {
        return;
    }

    gameGraph->releasePoint(this->pos);
    this->pos = destination;
    gameGraph->busyPoint(this->pos);
}

bool Entity::isAlive() {
    return alive;
}

const Point& Entity::getPos() const {
    return pos;
}

Path Entity::makePath(const Point& destination) {
    gameGraph->releasePoint(this->pos);
    Path path = gameGraph->makePath(this->pos, destination);
    gameGraph->busyPoint(this->pos);

    return path;
}
