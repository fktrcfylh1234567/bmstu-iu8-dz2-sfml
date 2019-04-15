//
// Created by fktrc on 25.03.19.
//

#ifndef GAME_GAMEINSTANCE_HPP
#define GAME_GAMEINSTANCE_HPP

#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <memory>

#include "GameGraph.hpp"
#include "Character.hpp"
#include "Sequence.hpp"

class GameInstance {
public:
    GameInstance();
    void updateSequences(size_t currentTime);

    size_t spawnPlayer(size_t)

private:
    GameGraph gameGraph;
    std::map<size_t, Character> entities;
    std::map<size_t, std::unique_ptr<Sequence>> sequences;

    size_t nextEntityId = 1;
    size_t nextSequenceId = 1;

    const size_t locationSize = 3;
};

#endif //GAME_GAMEINSTANCE_HPP
