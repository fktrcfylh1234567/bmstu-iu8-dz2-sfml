//
// Created by fktrc on 12.04.19.
//

#ifndef GAME_GAMEMATCH_HPP
#define GAME_GAMEMATCH_HPP

#include <atomic>
#include <chrono>
#include <thread>
#include <iostream>

#include "IMatch.hpp"
#include "IInstance.hpp"
#include "ConcurrentQueue.hpp"
#include "LevelInstance.hpp"

class GameMatch : public IMatch {
public:
    void run() override;
    void stop() override;
    void handleAction(std::shared_ptr<IPlayerAction> action) override;

private:
    std::shared_ptr<IInstance> gameInstance;
    ConcurrentQueue<size_t> queue;
    std::atomic_bool isRunning = false;
    std::atomic_size_t timeCurrent = 0;

    const size_t locationSize = 3;
    const size_t timeUnitMs = 500;
};

#endif //GAME_GAMEMATCH_HPP
