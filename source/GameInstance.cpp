//
// Created by fktrc on 25.03.19.
//

#include <GameInstance.hpp>

GameInstance::GameInstance(const size_t locationSize) : locationSize(locationSize) {
    graph = std::make_shared<Graph>(locationSize);
}

void GameInstance::loadLocation(std::shared_ptr<ILocation> Ilocation) {
    graph->loadLocation(Ilocation);
}


void GameInstance::addGameRules(size_t gameModeId) {
    sequences[nextSequenceId] = std::make_unique<SequenceGameRulesTDM>(lastUpdateTime + 1, this);
    nextSequenceId++;
}

void GameInstance::update(size_t currentTime) {
    for (auto& sequence : sequences) {
        if (!sequence.second->isCanceled()) {
            if (sequence.second->getNextUpdateTime() == currentTime) {
                sequence.second->Update();
            }
        }
    }

    lastUpdateTime = currentTime;
}

size_t GameInstance::addCharacter(std::shared_ptr<ICharacterStats> characterStats) {
    size_t id = nextEntityId;
    nextEntityId++;
    characters.emplace(id, Character(id, graph, characterStats));
    return id;
}

void GameInstance::removeCharacter(size_t characterId) {
    characters.erase(characterId);
}

void GameInstance::addMoveSequence(size_t characterId, const Point& point) {
    sequences[nextSequenceId] = std::make_unique<SequenceCharacterMovement>(characterId, point, lastUpdateTime + 1,
                                                                            this);
    nextSequenceId++;
}

void GameInstance::addAttackSequence(size_t characterId, size_t targetId) {
    sequences[nextSequenceId] = std::make_unique<SequenceCharacterAttack>(characterId, targetId, lastUpdateTime + 1,
                                                                          this);
    nextSequenceId++;
}

void GameInstance::removeCharacterActiveSequence(size_t characterId) {

}

std::shared_ptr<IGraph> GameInstance::getGraph() {
    return graph;
}

std::map<size_t, Character>& GameInstance::getCharacters() {
    return characters;
}
