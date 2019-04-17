//
// Created by fktrc on 25.03.19.
//

#include <GameInstance.hpp>

GameInstance::GameInstance() {
    graph = std::make_shared<GameGraph>(locationSize);
}

void GameInstance::update(size_t currentTime) {
}

size_t GameInstance::spawnCharacter(std::shared_ptr<CharacterStats> characterStats) {
    return 0;
}

void GameInstance::removeCharacter(size_t characterId) {

}

void GameInstance::addMoveSequence(size_t characterId, Point& point) {
    sequences[nextSequenceId] = std::make_unique<MovementSequence>(characterId, point, this);
    nextSequenceId++;
}

void GameInstance::addAttackSequence(size_t characterId, size_t targetId) {

}

void GameInstance::removeCharacterActiveSequence(size_t characterId) {

}

std::shared_ptr<Graph> GameInstance::getGraph() {
    return graph;
}

std::map<size_t, Character>& GameInstance::getCharacters() {
    return characters;
}
