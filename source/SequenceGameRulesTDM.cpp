//
// Created by fktrc on 19.04.19.
//

#include <SequenceGameRulesTDM.hpp>
#include <iostream>

SequenceGameRulesTDM::SequenceGameRulesTDM(size_t nextUpdateTime, IGameInstance* levelInstance) :
        nextUpdateTime(nextUpdateTime), gameInstance(levelInstance) {}

void SequenceGameRulesTDM::Update() {
    for (auto& character : gameInstance->getCharacters()) {
        if (!character.second.isAlive()) {
            respawn(character.second.getId());
        }
    }
    nextUpdateTime++;
}

void SequenceGameRulesTDM::Cancel() {
    canceled = true;
}

bool SequenceGameRulesTDM::isCanceled() {
    return canceled;
}

size_t SequenceGameRulesTDM::getNextUpdateTime() {
    return nextUpdateTime;
}

void SequenceGameRulesTDM::addTeamMember(size_t characterId, size_t teamId) {
    charactersTeams.emplace(characterId, teamId);
}

void SequenceGameRulesTDM::respawn(size_t characterId) {
    size_t teamID = charactersTeams.at(characterId);
    std::shared_ptr<IGameModeInfo> info = gameInstance->getLevel()->getGameModeInfo(1);
    IGameModeInfoTDM* tdmInfo = dynamic_cast<IGameModeInfoTDM*>(info.get());

    for (const Point& point : tdmInfo->getTeamSpawnPoints(teamID)) {
        if (gameInstance->getGraph()->isFree(point)) {
            gameInstance->getCharacters().at(characterId).spawn(point);
            gameInstance->addGameEvent(GAME_EVENT_ENTITY_IS_ALIVE_CHANGED, characterId, 1);
            return;
        }
    }
}

size_t SequenceGameRulesTDM::getSequenceID() {
    return 1;
}
