//
// Created by fktrc on 26.03.19.
//

#ifndef GAME_SEQUENCE_HPP
#define GAME_SEQUENCE_HPP

#include <cstdio>
#include <chrono>

class Sequence {
public:
    virtual void Update(size_t currentTime) = 0;

    void cancel() {
        canceled = true;
    }

    bool isCanceled() const {
        return canceled;
    }

    size_t getNextUpdateTime() const {
        return nextUpdateTimeMs;
    }

protected:
    bool canceled = false;
    size_t nextUpdateTimeMs = 0;
};

#endif //GAME_SEQUENCE_HPP
