//
// Created by fktrc on 19.04.19.
//

#ifndef GAME_SEQUENCEGAMERULESTDM_HPP
#define GAME_SEQUENCEGAMERULESTDM_HPP

#include <ISequence.hpp>
#include "IGameInstance.hpp"
#include <IGameModeInfoTDM.hpp>

#include <algorithm>

class SequenceGameRulesTDM : public ISequence {
public:
    SequenceGameRulesTDM(size_t nextUpdateTime, IGameInstance* levelInstance);

    void Update() override;
    void Cancel() override;
    bool isCanceled() override;
    size_t getNextUpdateTime() override;
    size_t getSequenceID() override;
    void addTeamMember(size_t characterId, size_t teamId);

private:
    void respawn(size_t characterId);

    bool canceled = false;
    size_t nextUpdateTime = 0;
    IGameInstance* gameInstance;

    // charId -> teamId
    std::map<size_t, size_t> charactersTeams;
};

#endif //GAME_SEQUENCEGAMERULESTDM_HPP
