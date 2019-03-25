//
// Created by fktrc on 25.03.19.
//

#ifndef GAME_GAMEINSTANCE_HPP
#define GAME_GAMEINSTANCE_HPP

#include <cstdio>
#include <utility>
#include <vector>
#include <string>
#include <atomic>

#include "GameGraph.hpp"
#include "Entity.hpp"

class GameInstance {
public:
    GameInstance();

    void loadLocation(std::string &filename);

    void run();
    void stop();

private:
    GameGraph gameGraph;
    std::vector<Entity> entities;
    std::atomic_bool isRunning;
    size_t locationSize;
    size_t time;
};


#endif //GAME_GAMEINSTANCE_HPP
