//
// Created by fktrc on 25.03.19.
//

#include <GameGraph.hpp>

GameGraph::GameGraph(size_t locationSize) {
    this->locationSize = locationSize;
    graph = Graph();
}

void GameGraph::loadLocation(bool** location) {
    for (size_t i = 0; i < locationSize; i++) {
        for (size_t j = 0; j < locationSize; j++) {
            if (location[i][j]) {
                size_t id = pointToIndex(i, j);
                boost::add_edge(id, id, 0, graph);

                if (i != 0)
                    if (location[i - 1][j])
                        boost::add_edge(id, pointToIndex(i - 1, j), 1, graph);

                if (j != 0)
                    if (location[i][j - 1])
                        boost::add_edge(id, pointToIndex(i, j - 1), 1, graph);

                if (i != locationSize - 1)
                    if (location[i + 1][j])
                        boost::add_edge(id, pointToIndex(i + 1, j), 1, graph);

                if (j != locationSize - 1)
                    if (location[i][j + 1])
                        boost::add_edge(id, pointToIndex(i, j + 1), 1, graph);
            }
        }
    }
}

void GameGraph::busyPoint(const Point& point) {
    if (!isFree(point)) {
        return;
    }

    size_t id = pointToIndex(point);
    boost::remove_edge(id, id, graph);

    Graph::out_edge_iterator eit, eend;
    std::tie(eit, eend) = boost::out_edges(id, graph);
    std::set<size_t> linkedVertices;

    for (auto it = eit; it != eend; ++it) {
        linkedVertices.insert((*it).m_target);
    }

    for (auto it : linkedVertices) {
        boost::remove_edge(id, it, graph);
        boost::remove_edge(it, id, graph);
    }
}

void GameGraph::releasePoint(const Point& point) {
    if (isFree(point)) {
        return;
    }

    size_t id = pointToIndex(point);
    size_t x = point.first;
    size_t y = point.second;

    boost::add_edge(id, id, 0, graph);

    if (x != 0)
        if (isFree(x - 1, y)) {
            boost::add_edge(id, pointToIndex(x - 1, y), 1, graph);
            boost::add_edge(pointToIndex(x - 1, y), id, 1, graph);
        }

    if (y != 0)
        if (isFree(x, y - 1)) {
            boost::add_edge(id, pointToIndex(x, y - 1), 1, graph);
            boost::add_edge(pointToIndex(x, y - 1), id, 1, graph);
        }

    if (x != locationSize - 1)
        if (isFree(x + 1, y)) {
            boost::add_edge(id, pointToIndex(x + 1, y), 1, graph);
            boost::add_edge(pointToIndex(x + 1, y), id, 1, graph);
        }

    if (y != locationSize - 1)
        if (isFree(x, y + 1)) {
            boost::add_edge(id, pointToIndex(x, y + 1), 1, graph);
            boost::add_edge(pointToIndex(x, y + 1), id, 1, graph);
        }
}

bool GameGraph::isFree(const Point& point) {
    size_t id = pointToIndex(point);
    return (boost::in_degree(id, graph) != 0) && (boost::in_degree(id, graph) < 11);
}

bool GameGraph::isFree(const size_t x, const size_t y) {
    return isFree({x, y});
}

Path GameGraph::makePath(const Point& origin, const Point& destination) {
    size_t originId = pointToIndex(origin);
    size_t destId = pointToIndex(destination);

    boost::property_map<Graph, boost::edge_weight_t>::type weightmap = get(boost::edge_weight, graph);

    std::vector<vertex_descriptor> predecessor(num_vertices(graph));
    std::vector<int> distances(num_vertices(graph));

    vertex_descriptor source = vertex(originId, graph);
    vertex_descriptor goal = vertex(destId, graph);
    boost::dijkstra_shortest_paths(graph, source, boost::predecessor_map(&predecessor[0]).distance_map(&distances[0]));

    Path path;
    boost::graph_traits<Graph>::vertex_descriptor current = goal;

    if (current == predecessor[current]) {
        return path;
    }

    while (current != source) {
        path.push_back(indexToPoint(current));
        current = predecessor[current];
    }

    path.push_back(indexToPoint(source));
    std::reverse(path.begin(), path.end());

    return path;
}

size_t GameGraph::pointToIndex(const Point& point) {
    return locationSize * point.first + point.second;
}

size_t GameGraph::pointToIndex(const size_t x, const size_t y) {
    return locationSize * x + y;
}

Point GameGraph::indexToPoint(size_t p) {
    return {(p - p % locationSize) / locationSize, p % locationSize};
}

void GameGraph::debug_print_edges() {
    std::pair<Graph::vertex_iterator, Graph::vertex_iterator> vertices = boost::vertices(graph);
    std::pair<Graph::edge_iterator, Graph::edge_iterator> edges = boost::edges(graph);
    std::copy(edges.first, edges.second, std::ostream_iterator<Graph::edge_descriptor>{std::cout, "\n"});
}
