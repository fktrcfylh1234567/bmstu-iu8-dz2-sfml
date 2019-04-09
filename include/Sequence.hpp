//
// Created by fktrc on 26.03.19.
//

#ifndef GAME_SEQUENCE_HPP
#define GAME_SEQUENCE_HPP

#include <cstdio>
#include <chrono>
#include "GameInstance.hpp"

class GameInstance;

class Sequence {
public:
    Sequence(const size_t id, size_t nextUpdateTimeMs, GameInstance* instance) : Id(id),
                                                                                 nextUpdateTimeMs(nextUpdateTimeMs),
                                                                                 instance(instance) {}

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
    GameInstance* instance;
};

#endif //GAME_SEQUENCE_HPP
