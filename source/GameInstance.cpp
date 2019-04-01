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

void GameInstance::updateSequence(size_t sequenceId) {
    sequences[sequenceId]->Update();
}

void GameInstance::cancelSequence(size_t sequenceId) {
    sequences[sequenceId]->Cancel();
}

size_t GameInstance::getSequenceNexUpdateTime(size_t sequenceId) {
    return sequences[sequenceId]->getNextUpdateTime();
}

bool GameInstance::isSequenceCanceled(size_t sequenceId) {
    return sequences[sequenceId]->isCanceled();
}
