//
// Created by fktrc on 25.03.19.
//

#ifndef GAME_GAMEINSTANCE_HPP
#define GAME_GAMEINSTANCE_HPP

#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include "GameGraph.hpp"
#include "Entity.hpp"
#include "Sequence.hpp"
#include "DebugSequence.hpp"

class GameInstance {
public:
    GameInstance();

    size_t addEntity(size_t entityType);
    size_t addSequence(size_t sequenceType, size_t correntTime);
    void cancelSequence(size_t sequenceId);
    void updateSequences(size_t currentTime);

private:
    GameGraph gameGraph;
    std::map<size_t, Entity> entities;
    std::map<size_t, Sequence*> sequences;

    size_t nextEntityId = 1;
    size_t nextSequenceId = 1;

    const size_t locationSize = 3;
};

#endif //GAME_GAMEINSTANCE_HPP
