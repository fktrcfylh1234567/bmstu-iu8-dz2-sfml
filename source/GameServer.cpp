//
// Created by fktrc on 01.04.19.
//

#include <GameServer.hpp>

void GameServer::run() {
    std::cout << "Server was starded" << std::endl;
    sequences.push_back(gameInstance.addSequence(0, 1));

    isRunning = true;
    timeCurrent = 0;

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

            for (auto it = sequences.begin(); it != sequences.end(); ++it) {
                if (gameInstance.isSequenceCanceled(*it)) {
                    it = sequences.erase(it);
                    --it;
                    continue;
                }
                if (gameInstance.getSequenceNexUpdateTime(*it) == timeUpdate) {
                    gameInstance.updateSequence(*it);
                }
            }
        }
    }).detach();
}

void GameServer::stop() {
    isRunning = false;
    queue.push(0); // Let wait_and_pop() stop waiting
    std::cout << "Server was stopped on " << timeCurrent << std::endl;
}
