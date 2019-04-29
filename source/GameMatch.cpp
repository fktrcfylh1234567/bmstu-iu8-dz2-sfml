//
// Created by fktrc on 12.04.19.
//

#include "GameMatch.hpp"

void GameMatch::run() {
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
            gameInstance->update(timeUpdate);
        }
    }).detach();
}

void GameMatch::stop() {
    isRunning = false;
    queue.push(0); // Let wait_and_pop() stop waiting
    std::cout << "Game was stopped on " << timeCurrent << std::endl;
}
