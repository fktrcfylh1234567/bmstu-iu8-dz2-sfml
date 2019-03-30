//
// Created by fktrc on 25.03.19.
//

#include <GameInstance.hpp>

GameInstance::GameInstance() {
    gameGraph = GameGraph(locationSize);
}

void GameInstance::run() {
    isRunning = true;
    time = 0;

    std::thread([this]() {
        while (isRunning) {
            time++;
            queue.push(time);
            std::this_thread::sleep_for(std::chrono::milliseconds(timeUnitMs));
        }
    }).detach();

    std::thread([this]() {
        while (true) {
            size_t currentTime = queue.wait_and_pop();
            if (currentTime == 0) {
                break;
            }

            for (auto it = sequences.begin(); it != sequences.end(); ++it) {
                if ((*it)->isCanceled()) {
                    it = sequences.erase(it);
                    --it;
                    continue;
                }
                if ((*it)->getNextUpdateTime() == currentTime) {
                    (*it)->Update(currentTime);
                }
            }
        }
    }).detach();
}

void GameInstance::stop() {
    isRunning = false;
    queue.push(0); // Let wait_and_pop() stop waiting
    std::cout << "Game was stopped on " << time << std::endl;
}

void GameInstance::loadLocation(std::string& filename) {
    bool** location = new bool* [locationSize];
    for (size_t i = 0; i < locationSize; i++) {
        location[i] = new bool[locationSize];
    }

    gameGraph.loadLocation(location);

    for (size_t i = 0; i < locationSize; i++) {
        delete[] location[i];
    }
    delete[] location;
}
