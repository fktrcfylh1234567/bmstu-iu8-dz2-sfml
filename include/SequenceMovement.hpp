//
// Created by fktrc on 18.04.19.
//

#ifndef GAME_SEQUENCEMOVEMENT_HPP
#define GAME_SEQUENCEMOVEMENT_HPP

#include "ISequenceCharacter.hpp"
#include "ILevelInstance.hpp"

class SequenceMovement : public ISequenceCharacter {
public:
    SequenceMovement(size_t characterId, const Point& dest, size_t nextUpdateTime, ILevelInstance* levelInstance);

    void Update() override;
    void Cancel() override;
    bool isCanceled() override;
    size_t getNextUpdateTime() override;
    size_t getCharacterId() override;

private:
    bool canceled = false;
    size_t characterId = 0;
    const Point& dest;
    size_t nextUpdateTime = 0;
    ILevelInstance* levelInstance = nullptr;
    Path path;

    bool isPathValid();
};

#endif //GAME_SEQUENCEMOVEMENT_HPP
