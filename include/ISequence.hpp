//
// Created by fktrc on 26.03.19.
//

#ifndef GAME_ISEQUENCE_HPP
#define GAME_ISEQUENCE_HPP

#include <cstdio>
#include "EventEntityInstance.hpp"

class ISequence {
public:
    virtual void Update() = 0;
    virtual void Cancel() = 0;
    virtual bool isCanceled() = 0;
    virtual size_t getNextUpdateTime() = 0;
    virtual size_t getSequenceID() = 0;
};

#endif //GAME_ISEQUENCE_HPP
