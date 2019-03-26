//
// Created by fktrc on 25.03.19.
//

#ifndef GAME_GAMEGRAPH_HPP
#define GAME_GAMEGRAPH_HPP

#include <cstdio>
#include <utility>
#include <vector>

#include <algorithm>
#include <iterator>
#include <iostream>
#include <set>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>

typedef std::pair<size_t, size_t> Point;
typedef std::vector<Point> Path;

typedef boost::property<boost::edge_weight_t, int> EdgeWeightProperty;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property, EdgeWeightProperty> Graph;
typedef boost::graph_traits<Graph>::edge_iterator edge_iterator;
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_descriptor;

class GameGraph {
public:
    GameGraph() = default;

    explicit GameGraph(size_t locationSize);

    void loadLocation(bool** location);

    void busyPoint(const Point& point);

    void releasePoint(const Point& point);

    bool isFree(const Point& point);

    bool isFree(const size_t x, const size_t y);

    Path makePath(const Point& origin, const Point& destination);

    void debug_print_edges();

private:
    Graph graph;
    size_t locationSize;

    size_t pointToIndex(const Point& point);

    size_t pointToIndex(size_t x, size_t y);

    Point indexToPoint(size_t p);
};

#endif //GAME_GAMEGRAPH_HPP
