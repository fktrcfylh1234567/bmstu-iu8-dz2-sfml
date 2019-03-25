//
// Created by fktrc on 25.03.19.
//

#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include <cstdio>
#include <utility>

#include "GameGraph.hpp"

typedef std::pair<size_t, size_t> Point;

class Entity {
public:
    explicit Entity(GameGraph* gameGraph);

    void spawn(Point& pos);
    void setLocation(Point& pos);
    void destroy();

    bool isAlive();
private:
    Point pos;
    bool alive;
    GameGraph* gameGraph;
};


#endif //GAME_ENTITY_HPP
