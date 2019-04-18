//
// Created by fktrc on 18.04.19.
//

#ifndef GAME_SEQUENCEMOVEMENT_HPP
#define GAME_SEQUENCEMOVEMENT_HPP

#include "ISequence.hpp"
#include "ILevelInstance.hpp"

class SequenceMovement : public ISequence {
public:
    SequenceMovement(size_t characterId, Point& point, ILevelInstance* actionSpace);

    void Update() override;
    void Cancel() override;
    bool isCanceled() override;
    size_t getNextUpdateTime() override;

private:
    size_t characterId = 0;
    Point& point;
    ILevelInstance* actionSpace = nullptr;
};

#endif //GAME_SEQUENCEMOVEMENT_HPP
