//
// Created by fktrc on 25.03.19.
//

#include <GameInstance.hpp>

GameInstance::GameInstance(const size_t locationSize) : locationSize(locationSize) {
    graph = std::make_shared<Graph>(locationSize);
}

void GameInstance::loadLevel(std::shared_ptr<ILevel> level) {
    this->level = level;
    graph->loadLocation(this->level->getLocation());
}

void GameInstance::addGameRules(size_t gameModeId) {
    sequences.push_back(std::make_unique<SequenceGameRulesTDM>(lastUpdateTime + 1, this));
}

void GameInstance::update(size_t currentTime) {
    for (auto it = sequences.begin(); it != sequences.end(); it++) {
        if (it->operator->()->isCanceled()) {
            it = sequences.erase(it);
            it--;
        }
    }

    for (auto& sequence : sequences) {
        if (sequence->getNextUpdateTime() == currentTime) {
            sequence->Update();
        }
    }

    lastUpdateTime = currentTime;
}

std::queue<std::shared_ptr<IGameEvent>>& GameInstance::getGameInstanceUpdates() {
    return gameInstanceEvents;
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
    sequences.push_back(std::make_unique<SequenceCharacterMovement>(characterId, point, lastUpdateTime + 1,
                                                                    this));
}

void GameInstance::addAttackSequence(size_t characterId, size_t targetId) {
    sequences.push_back(std::make_unique<SequenceCharacterAttack>(characterId, targetId, lastUpdateTime + 1,
                                                                  this));
}

void GameInstance::cancelCharacterActiveSequences(size_t characterId) {
    for (auto& sequence : sequences) {
        if (sequence->isCanceled()) {
            continue;
        }

        ISequenceCharacter* sequenceCharacter = dynamic_cast<ISequenceCharacter*>(sequence.get());

        if (sequenceCharacter == nullptr) {
            continue;
        }

        if (sequenceCharacter->getCharacterId() == characterId) {
            sequence->Cancel();
        }

    }
}

std::shared_ptr<IGraph> GameInstance::getGraph() {
    return graph;
}

std::map<size_t, Character>& GameInstance::getCharacters() {
    return characters;
}

void GameInstance::addGameEvent(size_t actionId, size_t entityId, size_t value) {
    gameInstanceEvents.push(std::make_shared<GameEventEntityInstance>(actionId, entityId, value));
}

const size_t GameInstance::getLocationSize() const {
    return locationSize;
}

std::shared_ptr<ILevel> GameInstance::getLevel() {
    return std::shared_ptr<ILevel>();
}
