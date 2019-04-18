//
// Created by fktrc on 25.03.19.
//

#ifndef GAME_GAMELEVELINSTANCE_HPP
#define GAME_GAMELEVELINSTANCE_HPP

#include <vector>
#include <string>
#include <map>
#include <memory>

#include "GameInstance.hpp"
#include "LevelInstance.hpp"

#include "GameGraph.hpp"
#include "Character.hpp"

#include "SequenceMovement.hpp"
#include "SequenceAttack.hpp"

class GameLevelInstance : public GameInstance, public LevelInstance {
public:
    GameLevelInstance();

    // GameInstance
    void update(size_t currentTime) override;
    size_t spawnCharacter(std::shared_ptr<CharacterStats> characterStats) override;
    void removeCharacter(size_t characterId) override;
    void addMoveSequence(size_t characterId, Point& point) override;
    void addAttackSequence(size_t characterId, size_t targetId) override;
    void removeCharacterActiveSequence(size_t characterId) override;

    // LevelInstance
    std::shared_ptr<Graph> getGraph() override;
    std::map<size_t, Character>& getCharacters() override;

private:
    std::shared_ptr<Graph> graph;
    std::map<size_t, Character> characters;
    std::map<size_t, std::unique_ptr<Sequence>> sequences;

    size_t nextEntityId = 1;
    size_t nextSequenceId = 1;

    const size_t locationSize = 3;
};

#endif //GAME_GAMELEVELINSTANCE_HPP
