//
// Created by fktrc on 15.04.19.
//

#ifndef GAME_BUFFINSTANCE_HPP
#define GAME_BUFFINSTANCE_HPP

#include "IBuff.hpp"

class BuffInstance : public IBuff {
public:
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

    void setHealModifier(int healModifier) {
        this->healModifier = healModifier;
    }

    void setAttackDamageModifier(int attackDamageModifier) {
        this->attackDamageModifier = attackDamageModifier;
    }

    void setAttackRangeModifier(int attackRangeModifier) {
        this->attackRangeModifier = attackRangeModifier;
    }

    void setMoveSpeedModifier(float moveSpeedModifier) {
        this->moveSpeedModifier = moveSpeedModifier;
    }

    void setAttackSpeedModifier(float attackSpeedModifier) {
        this->attackSpeedModifier = attackSpeedModifier;
    }

private:
    int healModifier = 0;
    int attackDamageModifier = 0;
    int attackRangeModifier = 0;

    float moveSpeedModifier = 1;
    float attackSpeedModifier = 1;
};

#endif //GAME_BUFFINSTANCE_HPP
