//
// Created by fktrc on 25.03.19.
//

#include <gtest/gtest.h>
#include <memory>
#include "Graph.hpp"
#include "LocationInstance.hpp"

TEST(GraphTest, Create) {
    size_t locationSize = 3;

    std::unique_ptr<IGraph> graph(new Graph(locationSize));
    std::vector<std::vector<bool>> location = {{true,  true,  true},
                                               {true,  false, false},
                                               {false, false, true}};

    std::shared_ptr<ILocation> ilocation = std::make_shared<LocationInstance>(location);
    graph->loadLocation(ilocation);

    EXPECT_EQ(graph->isFree({0, 0}), true);
    EXPECT_EQ(graph->isFree({1, 1}), false);
    EXPECT_EQ(graph->isFree({2, 1}), false);
    EXPECT_EQ(graph->isFree({2, 2}), true);

    // Point out of range
    EXPECT_EQ(graph->isFree({20, 10}), false);
}

TEST(GraphTest, Busy) {
    size_t locationSize = 3;
    Graph gameGraph(locationSize);
    std::vector<std::vector<bool>> location = {{true, true, true},
                                               {true, true, true},
                                               {true, true, true}};

    std::shared_ptr<ILocation> ilocation = std::make_shared<LocationInstance>(location);
    gameGraph.loadLocation(ilocation);

    gameGraph.busyPoint({1, 1});
    gameGraph.busyPoint({2, 2});

    EXPECT_EQ(gameGraph.isFree({1, 1}), false);
    EXPECT_EQ(gameGraph.isFree({2, 2}), false);
}

TEST(GraphTest, Release) {
    size_t locationSize = 3;
    Graph gameGraph(locationSize);
    std::vector<std::vector<bool>> location = {{false, false, false},
                                               {false, false, false},
                                               {false, false, true}};

    std::shared_ptr<ILocation> ilocation = std::make_shared<LocationInstance>(location);
    gameGraph.loadLocation(ilocation);

    gameGraph.releasePoint({1, 1});
    gameGraph.releasePoint({2, 0});

    EXPECT_EQ(gameGraph.isFree({1, 1}), true);
    EXPECT_EQ(gameGraph.isFree({2, 0}), true);
}

TEST(GraphTest, Path) {
    size_t locationSize = 3;
    Graph gameGraph(locationSize);
    std::vector<std::vector<bool>> location = {{true,  true,  true},
                                               {true,  true,  false},
                                               {false, false, true}};

    std::shared_ptr<ILocation> ilocation = std::make_shared<LocationInstance>(location);
    gameGraph.loadLocation(ilocation);

    Path path = gameGraph.makePath({1, 0}, {0, 2});
    EXPECT_EQ(path[0], Point(1, 0));
    EXPECT_EQ(path[1], Point(0, 0));
    EXPECT_EQ(path[2], Point(0, 1));
    EXPECT_EQ(path[3], Point(0, 2));

    // Paths not exists
    EXPECT_TRUE(gameGraph.makePath({1, 0}, {1, 0}).empty());
    EXPECT_TRUE(gameGraph.makePath({0, 0}, {2, 2}).empty());
}
