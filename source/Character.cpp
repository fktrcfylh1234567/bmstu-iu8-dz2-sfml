//
// Created by fktrc on 08.04.19.
//

#include "Character.hpp"

Character::Character(size_t id, std::shared_ptr<Graph> gameGraph, const std::shared_ptr<CharacterStats> defaulStats)
        : id(id) {
    this->gameGraph = gameGraph;
    this->defaulStats = defaulStats;
}

void Character::spawn(const Point& destination) {
    if (!this->gameGraph->isFree(destination)) {
        return;
    }
    alive = true;
    this->pos = destination;
    gameGraph->busyPoint(this->pos);
    resetAllStatsToDefault();
    activeBuffs.clear();
}

void Character::kill() {
    alive = false;
    gameGraph->releasePoint(this->pos);
}

void Character::setPosition(const Point& destination) {
    if (!this->gameGraph->isFree(destination)) {
        return;
    }
    gameGraph->releasePoint(this->pos);
    this->pos = destination;
    gameGraph->busyPoint(this->pos);
}

Path Character::makePath(const Point& destination) {
    gameGraph->releasePoint(this->pos);
    Path path = gameGraph->makePath(this->pos, destination);
    gameGraph->busyPoint(this->pos);
    return path;
}

bool Character::isAlive() {
    return alive;
}

const Point& Character::getPos() const {
    return pos;
}

const size_t Character::getId() const {
    return id;
}

void Character::doDamage(size_t damage) {
    if (currentStats.getHp() < damage) {
        currentStats.setHp(0);
        this->alive = false;
        return;
    }
    currentStats.setHp(currentStats.getHp() - damage);
}

void Character::addBuff(std::shared_ptr<Buff> buff) {
    activeBuffs.push_back(buff);
    updateBuffs();
}

void Character::removeBuff(std::shared_ptr<Buff> buff) {
    for (auto it = activeBuffs.begin(); it != activeBuffs.end(); ++it) {
        if (*it == buff) {
            activeBuffs.erase(it);
            updateBuffs();
            return;
        }
    }
}

const CharacterStatsInstance& Character::getCurrentStats() const {
    return currentStats;
}

void Character::resetAllStatsToDefault() {
    currentStats.setHp(defaulStats->getHp());
    currentStats.setHeal(defaulStats->getHeal());
    currentStats.setMoveSpeed(defaulStats->getMoveSpeed());
    currentStats.setAttackDamage(defaulStats->getAttackDamage());
    currentStats.setAttackSpeed(defaulStats->getAttackSpeed());
    currentStats.setAttackRange(defaulStats->getAttackRange());
}

void Character::updateBuffs() {
    resetAllStatsToDefault();
    for (const auto buff : activeBuffs) {
        // Numerical
        currentStats.setHeal(currentStats.getHeal() + buff->getHealModifier());
        currentStats.setAttackDamage(currentStats.getAttackDamage() + buff->getAttackDamageModifier());
        currentStats.setAttackRange(currentStats.getAttackRange() + buff->getAttackRangeModifier());

        // Coefficents
        currentStats.setMoveSpeed(currentStats.getMoveSpeed() * buff->getMoveSpeedModifier());
        currentStats.setAttackSpeed(currentStats.getAttackSpeed() * buff->getAttackSpeedModifier());
    }
}
