//
// Created by fktrc on 11.04.19.
//

#ifndef GAME_BUFF_HPP
#define GAME_BUFF_HPP

#include <cstdio>

class Buff {
public:
    // Numerical
    virtual const int getHealModifier() const = 0;
    virtual const int getAttackDamageModifier() const = 0;
    virtual const int getAttackRangeModifier() const = 0;

    // Coefficents
    virtual const float getMoveSpeedModifier() const = 0;
    virtual const float getAttackSpeedModifier() const = 0;
};

#endif //GAME_BUFF_HPP
