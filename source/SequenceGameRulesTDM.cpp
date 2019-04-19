//
// Created by fktrc on 19.04.19.
//

#include <SequenceGameRulesTDM.hpp>

SequenceGameRulesTDM::SequenceGameRulesTDM(size_t nextUpdateTime, ILevelInstance* levelInstance) : nextUpdateTime(
        nextUpdateTime), levelInstance(levelInstance) {}

void SequenceGameRulesTDM::Update() {
    for (auto& character : levelInstance->getCharacters()) {
        if (!character.second.isAlive()) {
            character.second.spawn(Point(0, 0));
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
