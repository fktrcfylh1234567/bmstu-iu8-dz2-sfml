//
// Created by fktrc on 19.04.19.
//

#include <SequenceGameRulesTDM.hpp>

SequenceGameRulesTDM::SequenceGameRulesTDM(size_t nextUpdateTime, IGameInstance* levelInstance) : nextUpdateTime(
        nextUpdateTime), levelInstance(levelInstance) {}

void SequenceGameRulesTDM::Update() {
    for (auto& character : levelInstance->getCharacters()) {
        if (!character.second.isAlive()) {
            character.second.spawn(Point(0, 0));
            levelInstance->addGameEvent(GAME_EVENT_ENTITY_IS_ALIVE_CHANGED, character.second.getId(), 1);
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
