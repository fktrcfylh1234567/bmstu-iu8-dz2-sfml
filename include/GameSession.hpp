//
// Created by fktrc on 12.04.19.
//

#ifndef GAME_GAMESESSION_HPP
#define GAME_GAMESESSION_HPP

#include <Session.hpp>
#include <iostream>

#include <atomic>
#include <chrono>
#include <thread>

#include "GameInstance.hpp"
#include "ConcurrentQueue.hpp"

class GameSession : public Session {
    void run() override;
    void stop() override;
    void handleAction(UserAction action) override;

private:
    ConcurrentQueue<size_t> queue;
    std::atomic_bool isRunning = false;
    std::atomic_size_t timeCurrent = 0;

    const size_t locationSize = 3;
    const size_t timeUnitMs = 500;
};

#endif //GAME_GAMESESSION_HPP
