//
// Created by fktrc on 25.03.19.
//

#ifndef GAME_GAMEGRAPH_HPP
#define GAME_GAMEGRAPH_HPP

#include <cstdio>
#include <utility>
#include <vector>

typedef std::pair<size_t, size_t> Point;
typedef std::vector<Point> Path;

class GameGraph {
public:
    GameGraph() = default;

    void loadLocation(int** location);
    void busyPoint(Point& point);
    void releasePoint(Point& point);

    bool isFree(Point& point);
    Path makePath(Point& origin, Point& destination);
};

#endif //GAME_GAMEGRAPH_HPP
