//
// Created by fktrc on 12.04.19.
//

#ifndef GAME_MATCH_HPP
#define GAME_MATCH_HPP

#include <atomic>
#include <chrono>
#include <thread>
#include <iostream>

#include "IMatch.hpp"
#include "IInstance.hpp"
#include "ConcurrentQueue.hpp"
#include "LevelInstance.hpp"
#include "PlayerActionMove.hpp"
#include "PlayerActionAttack.hpp"

#include "level_1.hpp"
#include "character_1.hpp"
#include "character_2.hpp"

class Match : public IMatch {
public:
    void setupGame(std::string levelName, size_t gameModeId) override;
    void addPlayer(size_t playerId, size_t charStatsId) override;

    void run() override;
    void stop() override;
    bool isRunning() override;

    void handleAction(std::shared_ptr<IPlayerAction> action) override;

private:
    std::shared_ptr<IInstance> instance;
    ConcurrentQueue<size_t> queue;
    std::atomic_bool running = false;
    std::atomic_size_t currentTime = 0;

    // playerId -> charId
    std::map<size_t, size_t> players;

    const size_t timeUnitMs = 500;
};

#endif //GAME_MATCH_HPP
