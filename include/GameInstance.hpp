//
// Created by fktrc on 25.03.19.
//

#ifndef GAME_GAMEINSTANCE_HPP
#define GAME_GAMEINSTANCE_HPP

#include <vector>
#include <string>
#include <map>
#include <queue>
#include <memory>

#include <IInstance.hpp>
#include <IGameInstance.hpp>

#include "ILevel.hpp"
#include "Graph.hpp"
#include "Character.hpp"
#include "SequenceCharacterMovement.hpp"
#include "SequenceCharacterAttack.hpp"
#include "SequenceGameRulesTDM.hpp"
#include "EventEntityInstance.hpp"

class GameInstance : public IInstance, public IGameInstance {
public:
    explicit GameInstance(size_t locationSize);

    // IInstance
    void loadLevel(std::shared_ptr<ILevel> level) override;
    void addGameRules(size_t gameModeId) override;
    void update(size_t currentTime) override;
    std::queue<std::shared_ptr<IEvent>>& getGameInstanceUpdates() override;

    size_t addCharacter(std::shared_ptr<ICharacterStats> characterStats, size_t teamId) override;
    void removeCharacter(size_t characterId) override;
    void addMoveSequence(size_t characterId, const Point& point) override;
    void addAttackSequence(size_t characterId, size_t targetId) override;
    void cancelCharacterActiveSequences(size_t characterId) override;

    // IGameInstance
    std::shared_ptr<IGraph> getGraph() override;
    std::map<size_t, Character>& getCharacters() override;
    void addGameEvent(size_t actionId, size_t entityId, size_t value) override;
    const size_t getLocationSize() const override;
    std::shared_ptr<ILevel> getLevel() override;

private:
    std::shared_ptr<ILevel> level;
    std::shared_ptr<IGraph> graph;
    std::map<size_t, Character> characters;
    std::vector<std::unique_ptr<ISequence>> sequences;
    std::queue<std::shared_ptr<IEvent>> gameInstanceEvents;

    size_t lastUpdateTime = 0;
    size_t nextEntityId = 1;

    const size_t locationSize;
};

#endif //GAME_GAMEINSTANCE_HPP
