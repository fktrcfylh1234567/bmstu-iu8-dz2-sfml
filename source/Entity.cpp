//
// Created by fktrc on 25.03.19.
//

#include <Entity.hpp>

Entity::Entity(GameGraph* gameGraph) {
    this->gameGraph = gameGraph;
    alive = false;
}

void Entity::spawn(Point& pos) {
    alive = true;
    this->pos = pos;
    gameGraph->busyPoint(this->pos);
}

void Entity::destroy() {
    alive = false;
    gameGraph->releasePoint(this->pos);
}

void Entity::setLocation(Point& pos) {
    gameGraph->releasePoint(this->pos);
    this->pos = pos;
    gameGraph->busyPoint(this->pos);
}

bool Entity::isAlive() {
    return alive;
}
