//
// Created by fktrc on 25.03.19.
//

#include <GameInstance.hpp>

GameInstance::GameInstance() {
    gameGraph = GameGraph(locationSize);
    isRunning = false;
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

void GameInstance::loadLocation(char* filename) {
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
