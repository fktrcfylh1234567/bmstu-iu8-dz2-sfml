//
// Created by fktrc on 25.03.19.
//

#include <GameInstance.hpp>

GameInstance::GameInstance() {
    gameGraph = GameGraph(locationSize);
}

size_t GameInstance::addSequence(size_t sequenceType, size_t currentTime) {
    sequences[nextSequenceId] = new DebugSequence(nextSequenceId, currentTime + 1);
    ++nextSequenceId;
    return nextSequenceId - 1;
}

void GameInstance::cancelSequence(size_t sequenceId) {
    sequences[sequenceId]->Cancel();
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
