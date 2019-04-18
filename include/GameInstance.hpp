//
// Created by fktrc on 25.03.19.
//

#ifndef GAME_GAMEINSTANCE_HPP
#define GAME_GAMEINSTANCE_HPP

#include <vector>
#include <string>
#include <map>
#include <memory>

#include "IGameInstance.hpp"
#include "ILevelInstance.hpp"

#include "Graph.hpp"
#include "Character.hpp"

#include "SequenceMovement.hpp"
#include "SequenceAttack.hpp"

class GameInstance : public IGameInstance, public ILevelInstance {
public:
    GameInstance();

    // IGameInstance
    void update(size_t currentTime) override;
    size_t spawnCharacter(std::shared_ptr<ICharacterStats> characterStats) override;
    void removeCharacter(size_t characterId) override;
    void addMoveSequence(size_t characterId, Point& point) override;
    void addAttackSequence(size_t characterId, size_t targetId) override;
    void removeCharacterActiveSequence(size_t characterId) override;

    // ILevelInstance
    std::shared_ptr<IGraph> getGraph() override;
    std::map<size_t, Character>& getCharacters() override;

private:
    std::shared_ptr<IGraph> graph;
    std::map<size_t, Character> characters;
    std::map<size_t, std::unique_ptr<ISequence>> sequences;

    size_t nextEntityId = 1;
    size_t nextSequenceId = 1;

    const size_t locationSize = 3;
};

#endif //GAME_GAMEINSTANCE_HPP
