//
// Created by fktrc on 18.04.19.
//

#ifndef GAME_ACTIONSPACE_HPP
#define GAME_ACTIONSPACE_HPP

#include <map>

#include "Graph.hpp"
#include "Character.hpp"
#include "Sequence.hpp"

class ActionSpace {
public:
    virtual std::shared_ptr<Graph> getGraph() = 0;
    virtual std::map<size_t, Character>& getCharacters() = 0;
};

#endif //GAME_ACTIONSPACE_HPP
