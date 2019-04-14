//
// Created by fktrc on 08.04.19.
//

#include "Character.hpp"

Character::Character(const size_t id, Graph* gameGraph, const CharacterStats& defaulStats)
        : Id(id), gameGraph(gameGraph), defaulStats(defaulStats) {
    resetAllStatsToDefault();
}

void Character::spawn(const Point& destination) {
    if (!this->gameGraph->isFree(destination)) {
        return;
    }

    alive = true;
    this->pos = destination;
    gameGraph->busyPoint(this->pos);
    resetAllStatsToDefault();
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
    return Id;
}

void Character::doDamage(size_t damage) {
    if (currentStats.hp < damage) {
        currentStats.hp = 0;
        this->alive = false;
        return;
    }
    currentStats.hp -= damage;
}

void Character::addBuff(Buff* buff) {
    activeBuffs.push_back(buff);
}

void Character::removeBuff(Buff* buff) {
    for (auto it = activeBuffs.begin(); it != activeBuffs.end(); ++it) {
        if (*it == buff) {
            activeBuffs.erase(it);
            return;
        }
    }
}

void Character::updateBuffs() {
    resetAllStatsToDefault();
    for (const Buff* buff : activeBuffs) {
        // Numerical
        currentStats.heal += buff->healModifier;
        currentStats.attackDamage += buff->attackDamageModifier;

        // Coefficents
        currentStats.moveSpeed *= buff->moveSpeedModifier;
        currentStats.attackSpeed *= buff->attackSpeedModifier;
        currentStats.attackRange *= buff->attackRangeModifier;

        // Flags
        if (buff->stunned) {
            stunned = true;
        }
        if (buff->immunityFromBasicAttack) {
            immunityFromBasicAttack = true;
        }
        if (buff->immunityFromSpells) {
            immunityFromSpells = true;
        }

    }
}

bool Character::isStunned() const {
    return stunned;
}

bool Character::isImmunityFromBasicAttack() const {
    return immunityFromBasicAttack;
}

bool Character::isImmunityFromSpells() const {
    return immunityFromSpells;
}

void Character::resetAllStatsToDefault() {
    currentStats = defaulStats;

    stunned = false;
    immunityFromBasicAttack = false;
    immunityFromSpells = false;
}

const CharacterStats& Character::getCurrentStats() const {
    return currentStats;
}
