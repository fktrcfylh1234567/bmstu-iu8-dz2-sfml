//
// Created by fktrc on 18.04.19.
//

#ifndef GAME_SEQUENCECHARACTERMOVEMENT_HPP
#define GAME_SEQUENCECHARACTERMOVEMENT_HPP

#include "ISequenceCharacter.hpp"
#include "ILevelInstance.hpp"

class SequenceCharacterMovement : public ISequenceCharacter {
public:
    SequenceCharacterMovement(size_t characterId, const Point& dest, size_t nextUpdateTime,
                              ILevelInstance* levelInstance);

    void Update() override;
    void Cancel() override;
    bool isCanceled() override;
    size_t getNextUpdateTime() override;
    size_t getCharacterId() override;

private:
    bool canceled = false;
    const size_t characterId = 0;
    Point dest;
    size_t nextUpdateTime = 0;
    ILevelInstance* levelInstance = nullptr;
    Path path;

    void updatePath();
    bool isPathValid();
    void makePath();
};

#endif //GAME_SEQUENCECHARACTERMOVEMENT_HPP
