//
// Created by fktrc on 25.03.19.
//

#include <GameLevelInstance.hpp>

GameLevelInstance::GameLevelInstance() {
    graph = std::make_shared<GameGraph>(locationSize);
}

void GameLevelInstance::update(size_t currentTime) {
}

size_t GameLevelInstance::spawnCharacter(std::shared_ptr<CharacterStats> characterStats) {
    return 0;
}

void GameLevelInstance::removeCharacter(size_t characterId) {

}

void GameLevelInstance::addMoveSequence(size_t characterId, Point& point) {
    sequences[nextSequenceId] = std::make_unique<SequenceMovement>(characterId, point, this);
    nextSequenceId++;
}

void GameLevelInstance::addAttackSequence(size_t characterId, size_t targetId) {

}

void GameLevelInstance::removeCharacterActiveSequence(size_t characterId) {

}

std::shared_ptr<Graph> GameLevelInstance::getGraph() {
    return graph;
}

std::map<size_t, Character>& GameLevelInstance::getCharacters() {
    return characters;
}
