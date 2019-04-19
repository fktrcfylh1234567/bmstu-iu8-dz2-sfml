//
// Created by fktrc on 19.04.19.
//

#ifndef GAME_SEQUENCEGAMERULESTDM_HPP
#define GAME_SEQUENCEGAMERULESTDM_HPP

#include "ISequence.hpp"
#include "ILevelInstance.hpp"

class SequenceGameRulesTDM : public ISequence {
public:
    SequenceGameRulesTDM(size_t nextUpdateTime, ILevelInstance* levelInstance);

    void Update() override;
    void Cancel() override;
    bool isCanceled() override;
    size_t getNextUpdateTime() override;

private:
    bool canceled = false;
    size_t nextUpdateTime = 0;
    ILevelInstance* levelInstance;
};


#endif //GAME_SEQUENCEGAMERULESTDM_HPP
