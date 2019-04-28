//
// Created by fktrc on 19.04.19.
//

#ifndef GAME_SEQUENCEGAMERULESTDM_HPP
#define GAME_SEQUENCEGAMERULESTDM_HPP

#include <ISequence.hpp>
#include "IGameInstance.hpp"
#include <ILevelGameModeInfoTDM.hpp>

class SequenceGameRulesTDM : public ISequence {
public:
    SequenceGameRulesTDM(size_t nextUpdateTime, IGameInstance* levelInstance);

    void Update() override;
    void Cancel() override;
    bool isCanceled() override;
    size_t getNextUpdateTime() override;

private:
    bool canceled = false;
    size_t nextUpdateTime = 0;
    IGameInstance* levelInstance;

    std::map<size_t, std::vector<size_t>> teams;
    std::map<size_t, size_t> teamScores;
};

#endif //GAME_SEQUENCEGAMERULESTDM_HPP
