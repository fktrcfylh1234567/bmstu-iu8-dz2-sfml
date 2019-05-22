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
    void addPlayer(size_t playerId, size_t charStatsId, size_t teamId) override;

    void run() override;
    void stop() override;
    bool isRunning() override;

    void handleAction(std::shared_ptr<IPlayerAction> action) override;
    std::queue<std::shared_ptr<IGameEvent>>& getGameEvents() override;

private:
    std::shared_ptr<IInstance> instance;
    ConcurrentQueue<size_t> updateCalls;
    std::atomic_bool running = false;
    std::atomic_size_t currentTime = 0;

    std::map<size_t, size_t> players; // playerId -> charId
    std::queue<std::shared_ptr<IGameEvent>> gameEvents;

    const size_t timeUnitMs = 500;
};

#endif //GAME_MATCH_HPP
