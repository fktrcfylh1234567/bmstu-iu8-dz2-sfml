//
// Created by fktrc on 11.04.19.
//

#ifndef GAME_BUFF_HPP
#define GAME_BUFF_HPP

#include <cstdio>

class Buff {
public:
    bool operator==(const Buff& rhs) const {
        return getHealModifier() == rhs.getHealModifier() &&
               getAttackDamageModifier() == rhs.getAttackDamageModifier() &&
               getAttackRangeModifier() == rhs.getAttackRangeModifier() &&
               getMoveSpeedModifier() == rhs.getMoveSpeedModifier() &&
               getAttackSpeedModifier() == rhs.getAttackSpeedModifier() &&
               isStunned() == rhs.isStunned() &&
               isImmunityFromBasicAttack() == rhs.isImmunityFromBasicAttack() &&
               isImmunityFromSpells() == rhs.isImmunityFromSpells();
    }

    bool operator!=(const Buff& rhs) const {
        return !(rhs == *this);
    }

    // Numerical
    virtual const int getHealModifier() const = 0;
    virtual const int getAttackDamageModifier() const = 0;
    virtual const int getAttackRangeModifier() const = 0;

    // Coefficents
    virtual const float getMoveSpeedModifier() const = 0;
    virtual const float getAttackSpeedModifier() const = 0;

    // Flags
    virtual const bool isStunned() const = 0;
    virtual const bool isImmunityFromBasicAttack() const = 0;
    virtual const bool isImmunityFromSpells() const = 0;
};

#endif //GAME_BUFF_HPP
