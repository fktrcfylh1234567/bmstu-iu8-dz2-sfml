//
// Created by fktrc on 11.04.19.
//

#ifndef GAME_BUFF_HPP
#define GAME_BUFF_HPP

#include <cstdio>

class Buff {
public:
    // Numerical
    virtual int getHealModifier() = 0;
    virtual size_t getAttackDamageModifier() = 0;
    virtual size_t getAttackRangeModifier() = 0;

    // Coefficents
    virtual float getMoveSpeedModifier() = 0;
    virtual float getAttackSpeedModifier() = 0;

    // Flags
    virtual bool isStunned() = 0;
    virtual bool isImmunityFromBasicAttack() = 0;
    virtual bool isImmunityFromSpells() = 0;
};

#endif //GAME_BUFF_HPP
