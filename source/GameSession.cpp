//
// Created by fktrc on 12.04.19.
//

#include "GameSession.hpp"

void GameSession::run() {
    isRunning = true;
    timeCurrent = 0;
    std::cout << "Game was starded" << std::endl;

    std::thread([this]() {
        while (isRunning) {
            timeCurrent++;
            queue.push(timeCurrent);
            std::this_thread::sleep_for(std::chrono::milliseconds(timeUnitMs));
        }
    }).detach();

    std::thread([this]() {
        while (true) {
            size_t timeUpdate = queue.wait_and_pop();
            if (timeUpdate == 0) {
                break;
            }
            gameInstance.updateSequences(timeUpdate);
        }
    }).detach();
}

void GameSession::stop() {
    isRunning = false;
    queue.push(0); // Let wait_and_pop() stop waiting
    std::cout << "Game was stopped on " << timeCurrent << std::endl;
}
