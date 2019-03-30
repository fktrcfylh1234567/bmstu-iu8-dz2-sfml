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
#include <chrono>
#include <thread>

#include "GameGraph.hpp"
#include "Entity.hpp"
#include "ConcurrentQueue.hpp"
#include "Sequence.hpp"

#include <iostream>

class GameInstance {
public:
    explicit GameInstance();
    void loadLocation(std::string& filename);

    void run();
    void stop();

private:
    GameGraph gameGraph;
    std::vector<Entity> entities;
    std::vector<Sequence*> sequences;

    ConcurrentQueue<size_t> queue;
    std::atomic_bool isRunning = false;
    std::atomic_size_t time = 0;

    const size_t locationSize = 3;
    const size_t timeUnitMs = 500;
};

#endif //GAME_GAMEINSTANCE_HPP
