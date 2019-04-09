//
// Created by fktrc on 25.03.19.
//

#include <GameInstance.hpp>

GameInstance::GameInstance() {
    gameGraph = Graph(locationSize);
}

void GameInstance::updateSequences(size_t currentTime) {
    for (auto itr = sequences.begin(); itr != sequences.end(); ++itr) {
        if (itr->second->isCanceled()) {
            sequences.erase(itr);
        }
    }

    for (auto sequence : sequences) {
        if (sequence.second->getNextUpdateTime() == currentTime) {
            sequence.second->Update();
        }
    }
}
