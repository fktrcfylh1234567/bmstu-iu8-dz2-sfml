//
// Created by fktrc on 25.03.19.
//

#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include <cstdio>
#include <utility>

#include "GameGraph.hpp"

typedef std::pair<size_t, size_t> Point;
typedef std::vector<Point> Path;

class Entity {
public:
    explicit Entity(GameGraph* gameGraph);

    void spawn(const Point& pos);
    void setPosition(const Point& pos);
    void destroy();

    bool isAlive();
    const Point& getPos() const;
    Path makePath(const Point& origin, const Point& destination);

private:
    Point pos = {0, 0};
    bool alive = false;
    GameGraph* gameGraph;
};

#endif //GAME_ENTITY_HPP
