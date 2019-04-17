//
// Created by fktrc on 18.04.19.
//

#ifndef GAME_ATTACKSEQUENCE_HPP
#define GAME_ATTACKSEQUENCE_HPP

#include "Sequence.hpp"

class AttackSequence : public Sequence {
public:
    void Update() override;
    void Cancel() override;
    bool isCanceled() override;
    size_t getNextUpdateTime() override;
};


#endif //GAME_ATTACKSEQUENCE_HPP
