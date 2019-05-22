//
// Created by fktrc on 12.04.19.
//

#include "Match.hpp"

void Match::setupGame(std::string levelName, size_t gameModeId) {
    if (running)
        return;

    instance->addGameRules(gameModeId);

    if (levelName == "level_1") {
        std::shared_ptr<level_1> level = std::make_shared<level_1>();
        instance->loadLevel(level);
        return;
    }
}

void Match::addPlayer(size_t playerId, size_t charStatsId) {
    if (running)
        return;
}

void Match::run() {
    running = true;
    currentTime = 0;
    std::cout << "Game was starded" << std::endl;

    std::thread([this]() {
        while (running) {
            currentTime++;
            queue.push(currentTime);
            std::this_thread::sleep_for(std::chrono::milliseconds(timeUnitMs));
        }
    }).detach();

    std::thread([this]() {
        while (true) {
            size_t timeUpdate = queue.wait_and_pop();
            if (timeUpdate == 0) {
                break;
            }
            instance->update(timeUpdate);
        }
    }).detach();
}

void Match::stop() {
    running = false;
    queue.push(0); // Let wait_and_pop() stop waiting
    std::cout << "Game was stopped on " << currentTime << std::endl;
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
