//
// Created by fktrc on 26.03.19.
//

#ifndef GAME_SEQUENCE_HPP
#define GAME_SEQUENCE_HPP

#include <cstdio>
#include <chrono>

class Sequence {
public:
    Sequence() = default;

    void Update();

    bool isCanceled() const;
    size_t getNextUpdateTime() const;

private:
    bool canceled = false;
    size_t nextUpdateTimeMs = 0;
};

#endif //GAME_SEQUENCE_HPP
