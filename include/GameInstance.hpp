//
// Created by fktrc on 25.03.19.
//

#ifndef GAME_GAMEINSTANCE_HPP
#define GAME_GAMEINSTANCE_HPP

#include <vector>
#include <string>
#include <map>
#include <memory>

#include "Instance.hpp"
#include "ActionSpace.hpp"

#include "GameGraph.hpp"
#include "Character.hpp"

#include "MovementSequence.hpp"
#include "AttackSequence.hpp"

class GameInstance : public Instance, public ActionSpace {
public:
    GameInstance();

    // Instance
    void update(size_t currentTime) override;
    size_t spawnCharacter(std::shared_ptr<CharacterStats> characterStats) override;
    void removeCharacter(size_t characterId) override;
    void addMoveSequence(size_t characterId, Point& point) override;
    void addAttackSequence(size_t characterId, size_t targetId) override;
    void removeCharacterActiveSequence(size_t characterId) override;

    // ActionSpace
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

#endif //GAME_GAMEINSTANCE_HPP
