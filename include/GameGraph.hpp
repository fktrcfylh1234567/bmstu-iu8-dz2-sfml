//
// Created by fktrc on 25.03.19.
//

#ifndef GAME_GAMEGRAPH_HPP
#define GAME_GAMEGRAPH_HPP

#include <algorithm>
#include <iterator>
#include <set>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>

#include "Graph.hpp"

typedef boost::property<boost::edge_weight_t, int> EdgeWeightProperty;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property, EdgeWeightProperty> BoostGraph;
typedef boost::graph_traits<BoostGraph>::edge_iterator edge_iterator;
typedef boost::graph_traits<BoostGraph>::vertex_descriptor vertex_descriptor;

class GameGraph : public Graph {
public:
    explicit GameGraph(size_t locationSize);
    void loadLocation(std::vector<std::vector<bool>>& location) override;

    Path makePath(const Point& origin, const Point& destination) override;

    void busyPoint(const Point& point) override;
    void releasePoint(const Point& point) override;
    bool isFree(const Point& point) override;
    bool isFree(size_t x, size_t y) override;

private:
    BoostGraph graph;
    size_t locationSize;

    size_t pointToIndex(const Point& point);
    size_t pointToIndex(size_t x, size_t y);
    Point indexToPoint(size_t p);
};

#endif //GAME_GAMEGRAPH_HPP
