//
// Created by fktrc on 19.04.19.
//

#ifndef GAME_ISEQUENCECHARACTER_HPP
#define GAME_ISEQUENCECHARACTER_HPP

#include "ISequence.hpp"

class ISequenceCharacter : public ISequence {
public:
    virtual void Update() override = 0;
    virtual void Cancel() override = 0;
    virtual bool isCanceled() override = 0;
    virtual size_t getNextUpdateTime() override = 0;
    virtual size_t getCharacterId() = 0;
};

#endif //GAME_ISEQUENCECHARACTER_HPP
