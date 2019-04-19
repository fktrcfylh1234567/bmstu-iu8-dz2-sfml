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
#include "ISequenceCharacter.hpp"
#include "SequenceGameRulesTDM.hpp"

class GameInstance : public IGameInstance, public ILevelInstance {
public:
    GameInstance(const size_t locationSize);

    // IGameInstance
    void loadLocation(std::shared_ptr<ILocation> Ilocation) override;
    void addGameRules(size_t gameModeId) override;
    void update(size_t currentTime) override;
    size_t addCharacter(std::shared_ptr<ICharacterStats> characterStats) override;
    void removeCharacter(size_t characterId) override;
    void addMoveSequence(size_t characterId, const Point& point) override;
    void addAttackSequence(size_t characterId, size_t targetId) override;
    void removeCharacterActiveSequence(size_t characterId) override;

    // ILevelInstance
    std::shared_ptr<IGraph> getGraph() override;
    std::map<size_t, Character>& getCharacters() override;

private:
    std::shared_ptr<IGraph> graph;
    std::map<size_t, Character> characters;
    std::map<size_t, std::unique_ptr<ISequence>> sequences;

    size_t lastUpdateTime = 0;
    size_t nextEntityId = 1;
    size_t nextSequenceId = 1;

    const size_t locationSize;
};

#endif //GAME_GAMEINSTANCE_HPP
