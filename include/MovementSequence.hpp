//
// Created by fktrc on 18.04.19.
//

#ifndef GAME_MOVEMENTSEQUENCE_HPP
#define GAME_MOVEMENTSEQUENCE_HPP

#include "Sequence.hpp"
#include "ActionSpace.hpp"

class MovementSequence : public Sequence {
public:
    MovementSequence(size_t characterId, Point& point, ActionSpace* actionSpace);

    void Update() override;
    void Cancel() override;
    bool isCanceled() override;
    size_t getNextUpdateTime() override;

private:
    size_t characterId = 0;
    Point& point;
    ActionSpace* actionSpace = nullptr;
};

#endif //GAME_MOVEMENTSEQUENCE_HPP
