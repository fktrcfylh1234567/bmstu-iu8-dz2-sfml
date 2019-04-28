//
// Created by fktrc on 18.04.19.
//

#ifndef GAME_IGAMEINSTANCE_HPP
#define GAME_IGAMEINSTANCE_HPP

#include <map>

#include "IGraph.hpp"
#include "Character.hpp"
#include "ISequence.hpp"
#include "ILevel.hpp"

class IGameInstance {
public:
    virtual std::shared_ptr<IGraph> getGraph() = 0;
    virtual std::map<size_t, Character>& getCharacters() = 0;
    virtual void addGameEvent(size_t actionId, size_t entityId, size_t value) = 0;
    virtual const size_t getLocationSize() const = 0;
    virtual std::shared_ptr<ILevel> getLevel() = 0;
};

#endif //GAME_IGAMEINSTANCE_HPP
