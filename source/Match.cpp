//
// Created by fktrc on 12.04.19.
//


#include "Match.hpp"

void Match::setupGame(std::string levelName, size_t gameModeId) {
    if (running)
        return;

    if (levelName == "level_1") {
        instance = std::make_unique<GameInstance>(5);
        std::shared_ptr<level_1> level = std::make_shared<level_1>();
        instance->loadLevel(level);
        instance->addGameRules(gameModeId);
        return;
    }
}

void Match::addPlayer(size_t playerId, size_t charStatsId, size_t teamId) {
    if (running)
        return;

    if (charStatsId == 1) {
        std::shared_ptr<character_1> stats = std::make_shared<character_1>();
        size_t id = instance->addCharacter(stats, teamId);
        players[playerId] = id;
    }

    if (charStatsId == 2) {
        std::shared_ptr<character_2> stats = std::make_shared<character_2>();
        size_t id = instance->addCharacter(stats, teamId);
        players[playerId] = id;
    }
}

void Match::removePlayer(size_t playerId) {
    players.erase(playerId);
}

void Match::run() {
    running = true;
    currentTime = 0;
    std::cout << "Match was starded" << std::endl;
    gameEvents.push({std::make_shared<EventGameMode>(GAME_EVENT_MATCH_START)});

    std::thread([this]() {
        while (running) {
            currentTime++;
            updateCalls.push(currentTime);
            std::this_thread::sleep_for(std::chrono::milliseconds(timeUnitMs));
        }
    }).detach();

    std::thread([this]() {
        while (true) {
            size_t timeUpdate = updateCalls.wait_and_pop();
            if (timeUpdate == 0) {
                break;
            }
            instance->update(timeUpdate);

            std::queue<std::shared_ptr<IEvent>>& queue = instance->getGameInstanceUpdates();
            if (queue.empty()) {
                continue;
            }

            std::vector<std::shared_ptr<IEvent>> events;

            while (!queue.empty()) {
                events.push_back(queue.front());
                queue.pop();
            }

            gameEvents.push(events);
        }
    }).detach();
}

void Match::stop() {
    running = false;
    updateCalls.push(0); // Let wait_and_pop() stop waiting
    gameEvents.push({});
    std::cout << "Match was stopped on " << currentTime << std::endl;
    gameEvents.push({std::make_shared<EventGameMode>(GAME_EVENT_MATCH_STOP)});
}

bool Match::isRunning() {
    return running;
}

void Match::handleAction(std::shared_ptr<IPlayerAction> action) {
    size_t charId = players.at(action->getPlayerId());

    if (action->getActionId() == IPlayerAction::ActionIdMove) {
        PlayerActionMove* playerActionMove = dynamic_cast<PlayerActionMove*>(action.get());
        instance->addMoveSequence(charId, playerActionMove->getDest());
        return;
    }

    if (action->getActionId() == IPlayerAction::ActionIdAttack) {
        PlayerActionAttack* playerActionAttack = dynamic_cast<PlayerActionAttack*>(action.get());
        instance->addAttackSequence(charId, playerActionAttack->getTargetId());
        return;
    }
}

ConcurrentQueue<std::vector<std::shared_ptr<IEvent>>>& Match::getGameEvents() {
    return gameEvents;
}
