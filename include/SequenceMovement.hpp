//
// Created by fktrc on 18.04.19.
//

#ifndef GAME_SEQUENCEMOVEMENT_HPP
#define GAME_SEQUENCEMOVEMENT_HPP

#include "Sequence.hpp"
#include "LevelInstance.hpp"

class SequenceMovement : public Sequence {
public:
    SequenceMovement(size_t characterId, Point& point, LevelInstance* actionSpace);

    void Update() override;
    void Cancel() override;
    bool isCanceled() override;
    size_t getNextUpdateTime() override;

private:
    size_t characterId = 0;
    Point& point;
    LevelInstance* actionSpace = nullptr;
};

#endif //GAME_SEQUENCEMOVEMENT_HPP
