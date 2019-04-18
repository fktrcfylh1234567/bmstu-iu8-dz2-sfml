//
// Created by fktrc on 18.04.19.
//

#ifndef GAME_ILEVELINSTANCE_HPP
#define GAME_ILEVELINSTANCE_HPP

#include <map>

#include "IGraph.hpp"
#include "Character.hpp"
#include "ISequence.hpp"

class ILevelInstance {
public:
    virtual std::shared_ptr<IGraph> getGraph() = 0;
    virtual std::map<size_t, Character>& getCharacters() = 0;
};

#endif //GAME_ILEVELINSTANCE_HPP
