//
// Created by fktrc on 25.03.19.
//

#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include <cstdio>
#include <utility>

#include "Graph.hpp"

typedef std::pair<size_t, size_t> Point;
typedef std::vector<Point> Path;

class Entity {
public:
    Entity(size_t Id, Graph* gameGraph);

    void spawn(const Point& destination);
    void kill();

    void setPosition(const Point& destination);
    Path makePath(const Point& destination);

    bool isAlive();
    const Point& getPos() const;
    const size_t getId() const;

protected:
    bool alive = false;
    const size_t Id;
    Point pos = {-1, -1};
    Graph* gameGraph;
};

#endif //GAME_ENTITY_HPP
