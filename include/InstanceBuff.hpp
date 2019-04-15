//
// Created by fktrc on 15.04.19.
//

#ifndef GAME_INSTANCEBUFF_HPP
#define GAME_INSTANCEBUFF_HPP

#include "Buff.hpp"

class InstanceBuff : public Buff {
public:
    int healModifier = 0;
    int attackDamageModifier = 0;
    int attackRangeModifier = 0;

    float moveSpeedModifier = 1;
    float attackSpeedModifier = 1;

    bool stunned = false;
    bool immunityFromBasicAttack = false;
    bool immunityFromSpells = false;

    const int getHealModifier() const override {
        return healModifier;
    }

    const int getAttackDamageModifier() const override {
        return attackDamageModifier;
    }

    const int getAttackRangeModifier() const override {
        return attackRangeModifier;
    }

    const float getMoveSpeedModifier() const override {
        return moveSpeedModifier;
    }

    const float getAttackSpeedModifier() const override {
        return attackSpeedModifier;
    }

    const bool isStunned() const override {
        return stunned;
    }

    const bool isImmunityFromBasicAttack() const override {
        return immunityFromBasicAttack;
    }

    const bool isImmunityFromSpells() const override {
        return immunityFromSpells;
    }
};

#endif //GAME_INSTANCEBUFF_HPP
