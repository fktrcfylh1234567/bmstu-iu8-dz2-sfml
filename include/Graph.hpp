//
// Created by fktrc on 14.04.19.
//

#ifndef GAME_GRAPH_HPP
#define GAME_GRAPH_HPP

#include <cstdio>
#include <utility>
#include <vector>

typedef std::pair<size_t, size_t> Point;
typedef std::vector<Point> Path;

class Graph {
public:
    virtual void loadLocation(std::vector<std::vector<bool>>& location) = 0;
    virtual void busyPoint(const Point& point) = 0;
    virtual void releasePoint(const Point& point) = 0;
    virtual bool isFree(const Point& point) = 0;
    virtual bool isFree(size_t x, size_t y) = 0;
    virtual Path makePath(const Point& origin, const Point& destination) = 0;
};

#endif //GAME_GRAPH_HPP
