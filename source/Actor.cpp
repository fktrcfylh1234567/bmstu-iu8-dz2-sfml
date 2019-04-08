//
// Created by fktrc on 08.04.19.
//

#include "Actor.hpp"

Actor::Actor(size_t id, Graph* gameGraph) : Entity(id, gameGraph) {}

void Actor::setDefaultStats(size_t hpDefault, int healDefault, size_t moveSpeedDefault, size_t damageDefault,
                            size_t attackSpeedDefault, size_t attackRangeDefault) {
    Actor::hpDefault = hpDefault;
    Actor::healDefault = healDefault;
    Actor::moveSpeedDefault = moveSpeedDefault;
    Actor::damageDefault = damageDefault;
    Actor::attackSpeedDefault = attackSpeedDefault;
    Actor::attackRangeDefault = attackRangeDefault;
    resetAllStatsToDefault();
}

void Actor::doDamage(size_t damage) {
    if (hp < damage) {
        hp = 0;
        this->alive = false;
        return;;
    }
    hp -= damage;
}

void Actor::addBuff(Buff* buff) {
    activeBuffs.push_back(buff);
}

void Actor::removeBuff(Buff* buff) {
    for (auto it = activeBuffs.begin(); it != activeBuffs.end(); ++it) {
        if (*it == buff) {
            activeBuffs.erase(it);
            return;
        }
    }
}

void Actor::updateBuffs() {
    resetAllStatsToDefault();
    for (const Buff* buff : activeBuffs) {
        // Numerical
        heal += (*buff).heal;
        damage += (*buff).damage;
        // Coefficents
        moveSpeed *= (*buff).moveSpeed;
        attackSpeed *= (*buff).attackSpeed;
        attackRange *= (*buff).attackRange;
        // Flags
        if ((*buff).stunned) {
            stunned = true;
        }
        if ((*buff).immunityFromBasicAttack) {
            immunityFromBasicAttack = true;
        }
        if ((*buff).immunityFromSpells) {
            immunityFromSpells = true;
        }

    }
}

size_t Actor::getHp() const {
    return hp;
}

int Actor::getHeal() const {
    return heal;
}

size_t Actor::getMoveSpeed() const {
    return moveSpeed;
}

size_t Actor::getDamage() const {
    return damage;
}

size_t Actor::getAttackSpeed() const {
    return attackSpeed;
}

size_t Actor::getAttackRange() const {
    return attackRange;
}

bool Actor::isStunned() const {
    return stunned;
}

bool Actor::isImmunityFromBasicAttack() const {
    return immunityFromBasicAttack;
}

bool Actor::isImmunityFromSpells() const {
    return immunityFromSpells;
}

void Actor::resetAllStatsToDefault() {
    hp = hpDefault;
    heal = healDefault;
    moveSpeed = moveSpeedDefault;
    damage = damageDefault;
    attackSpeed = attackSpeedDefault;
    attackRange = attackRangeDefault;

    stunned = false;
    immunityFromBasicAttack = false;
    immunityFromSpells = false;
}
