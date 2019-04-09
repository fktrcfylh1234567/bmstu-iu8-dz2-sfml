//
// Created by fktrc on 25.03.19.
//

#ifndef GAME_GAMEINSTANCE_HPP
#define GAME_GAMEINSTANCE_HPP

#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include "Graph.hpp"
#include "Actor.hpp"
#include "Sequence.hpp"

class GameInstance {
public:
    GameInstance();
    void updateSequences(size_t currentTime);

    size_t addEntity();
    void removeEntity(size_t entityId);
    Entity* getEntityById(size_t entityId);

    size_t addMoveSequence(size_t entityId, Point& pos, size_t correntTime);
    size_t addAttackSequence(size_t entityId, size_t targetId, size_t correntTime);
    void cancelSequence(size_t sequenceId);

private:
    Graph gameGraph;
    std::map<size_t, Entity> entities;
    std::map<size_t, Sequence*> sequences;

    size_t nextEntityId = 1;
    size_t nextSequenceId = 1;

    const size_t locationSize = 3;
};

#endif //GAME_GAMEINSTANCE_HPP
