//
// Created by fktrc on 15.04.19.
//

#ifndef GAME_CHARACTERSTATSINSTANCE_HPP
#define GAME_CHARACTERSTATSINSTANCE_HPP

#include "ICharacterStats.hpp"

class CharacterStatsInstance : public ICharacterStats {
public:
    size_t getHp() const override {
        return hp;
    }

    int getHeal() const override {
        return heal;
    }

    size_t getMoveSpeed() const override {
        return moveSpeed;
    }

    size_t getAttackDamage() const override {
        return attackDamage;
    }

    size_t getAttackSpeed() const override {
        return attackSpeed;
    }

    size_t getAttackRange() const override {
        return attackRange;
    }

    void setHp(size_t hp) {
        this->hp = hp;
    }

    void setHeal(int heal) {
        this->heal = heal;
    }

    void setMoveSpeed(size_t moveSpeed) {
        this->moveSpeed = moveSpeed;
    }

    void setAttackDamage(size_t attackDamage) {
        this->attackDamage = attackDamage;
    }

    void setAttackSpeed(size_t attackSpeed) {
        this->attackSpeed = attackSpeed;
    }

    void setAttackRange(size_t attackRange) {
        this->attackRange = attackRange;
    }

private:
    size_t hp = 0;
    int heal = 0;
    size_t moveSpeed = 0;
    size_t attackDamage = 0;
    size_t attackSpeed = 0;
    size_t attackRange = 0;
};

#endif //GAME_CHARACTERSTATSINSTANCE_HPP
