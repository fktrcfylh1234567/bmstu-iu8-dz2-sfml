//
// Created by fktrc on 25.03.19.
//

#include <GameInstance.hpp>

GameInstance::GameInstance() {
    isRunning = false;
    gameGraph = GameGraph();
    locationSize = 4;
}

void GameInstance::run() {
    isRunning = true;
    time = 0;
    while (isRunning) {
        time++;
    }
}

void GameInstance::stop() {
    isRunning = false;
}

void GameInstance::loadLocation(std::string &filename) {
    int** location = new int*[locationSize];
    for (size_t i = 0; i < locationSize; i++) {
        location[i] = new int[locationSize];
    }

    gameGraph.loadLocation(location);

    for (size_t i = 0; i < locationSize; i++) {
        delete[] location[i];
    }
    delete[] location;
}
