//
// Created by fktrc on 12.04.19.
//

#ifndef GAME_GAMESESSION_HPP
#define GAME_GAMESESSION_HPP

#include <atomic>
#include <chrono>
#include <thread>
#include <iostream>

#include "ISession.hpp"
#include "IInstance.hpp"
#include "ConcurrentQueue.hpp"
#include "LevelInstance.hpp"

class GameSession : public ISession {
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

#endif //GAME_GAMESESSION_HPP
