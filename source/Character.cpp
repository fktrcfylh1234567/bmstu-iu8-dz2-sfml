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
    if (currentStats.hp < damage) {
        currentStats.hp = 0;
        this->alive = false;
        return;
    }
    currentStats.hp -= damage;
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

const LocalCharacterStats& Character::getCurrentStats() const {
    return currentStats;
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
    currentStats.hp = defaulStats->getHp();
    currentStats.heal = defaulStats->getHeal();
    currentStats.moveSpeed = defaulStats->getMoveSpeed();
    currentStats.attackDamage = defaulStats->getAttackDamage();
    currentStats.attackSpeed = defaulStats->getAttackSpeed();
    currentStats.attackRange = defaulStats->getAttackRange();

    stunned = false;
    immunityFromBasicAttack = false;
    immunityFromSpells = false;
}

void Character::updateBuffs() {
    resetAllStatsToDefault();
    for (const auto buff : activeBuffs) {
        // Numerical
        currentStats.heal += buff->getHealModifier();
        currentStats.attackDamage += buff->getAttackDamageModifier();
        currentStats.attackRange += buff->getAttackRangeModifier();

        // Coefficents
        currentStats.moveSpeed *= buff->getMoveSpeedModifier();
        currentStats.attackSpeed *= buff->getAttackSpeedModifier();

        // Flags
        if (buff->isStunned()) {
            stunned = true;
        }
        if (buff->isImmunityFromBasicAttack()) {
            immunityFromBasicAttack = true;
        }
        if (buff->isImmunityFromSpells()) {
            immunityFromSpells = true;
        }
    }
}
