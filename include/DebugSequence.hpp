//
// Created by fktrc on 01.04.19.
//

#ifndef GAME_DEBUGSEQUENCE_HPP
#define GAME_DEBUGSEQUENCE_HPP

#include "Sequence.hpp"
#include <iostream>

class DebugSequence : public Sequence {
public:
    DebugSequence(const size_t id, size_t nextUpdateTimeMs) : Sequence(id, nextUpdateTimeMs) {}

private:
    void Update() override {
        std::cout << "Updated on " << nextUpdateTimeMs << std::endl;
        ++nextUpdateTimeMs;
    }
};

#endif //GAME_DEBUGSEQUENCE_HPP
