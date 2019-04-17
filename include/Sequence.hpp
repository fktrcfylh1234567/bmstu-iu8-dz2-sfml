//
// Created by fktrc on 26.03.19.
//

#ifndef GAME_SEQUENCE_HPP
#define GAME_SEQUENCE_HPP

#include <cstdio>

class Sequence {
public:
    virtual void Update() = 0;
    virtual void Cancel() = 0;
    virtual bool isCanceled() = 0;
    virtual size_t getNextUpdateTime() = 0;
};

#endif //GAME_SEQUENCE_HPP
