//
// Created by fktrc on 18.04.19.
//

#ifndef GAME_SEQUENCEATTACK_HPP
#define GAME_SEQUENCEATTACK_HPP

#include "ISequence.hpp"

class SequenceAttack : public ISequence {
public:
    void Update() override;
    void Cancel() override;
    bool isCanceled() override;
    size_t getNextUpdateTime() override;
};


#endif //GAME_SEQUENCEATTACK_HPP
