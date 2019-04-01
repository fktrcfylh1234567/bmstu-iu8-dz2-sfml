//
// Created by fktrc on 01.04.19.
//

#ifndef GAME_GAMESERVER_HPP
#define GAME_GAMESERVER_HPP

#include <iostream>

#include <atomic>
#include <chrono>
#include <thread>

#include "GameInstance.hpp"
#include "ConcurrentQueue.hpp"

class GameServer {
public:
    void run();
    void stop();

private:
    GameInstance gameInstance;
    std::vector<size_t> sequences;
    std::vector<size_t> entityIds;

    ConcurrentQueue<size_t> queue;
    std::atomic_bool isRunning = false;
    std::atomic_size_t timeCurrent = 0;

    const size_t locationSize = 3;
    const size_t timeUnitMs = 500;
};

#endif //GAME_GAMESERVER_HPP
