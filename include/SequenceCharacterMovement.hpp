//
// Created by fktrc on 18.04.19.
//

#ifndef GAME_SEQUENCECHARACTERMOVEMENT_HPP
#define GAME_SEQUENCECHARACTERMOVEMENT_HPP

#include <algorithm>

#include "ISequenceCharacter.hpp"
#include "IGameInstance.hpp"

class SequenceCharacterMovement : public ISequenceCharacter {
public:
    SequenceCharacterMovement(size_t characterId, const Point& dest, size_t nextUpdateTime,
                              IGameInstance* levelInstance);

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
    IGameInstance* levelInstance = nullptr;
    Path path;

    void updatePath();
    bool isPathValid();
    void makePath();

    size_t pointToIndex(const Point& point);
};

#endif //GAME_SEQUENCECHARACTERMOVEMENT_HPP
