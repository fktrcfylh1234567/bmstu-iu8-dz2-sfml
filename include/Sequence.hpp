//
// Created by fktrc on 26.03.19.
//

#ifndef GAME_SEQUENCE_HPP
#define GAME_SEQUENCE_HPP

#include <cstdio>
#include <chrono>

class Sequence {
public:
    Sequence(const size_t id, size_t nextUpdateTimeMs) : Id(id), nextUpdateTimeMs(nextUpdateTimeMs) {}

    virtual void Update() = 0;

    void Cancel() {
        canceled = true;
    }

    bool isCanceled() const {
        return canceled;
    }

    size_t getNextUpdateTime() const {
        return nextUpdateTimeMs;
    }

    const size_t getId() const {
        return Id;
    }

protected:
    const size_t Id;
    bool canceled = false;
    size_t nextUpdateTimeMs;
};

#endif //GAME_SEQUENCE_HPP
