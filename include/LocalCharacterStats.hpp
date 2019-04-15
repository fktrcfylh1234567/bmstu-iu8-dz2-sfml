//
// Created by fktrc on 15.04.19.
//

#ifndef GAME_LOCALCHARACTERSTATS_HPP
#define GAME_LOCALCHARACTERSTATS_HPP


#include "CharacterStats.hpp"

class LocalCharacterStats : public CharacterStats {
public:
    size_t hp = 0;
    int heal = 0;
    size_t moveSpeed = 0;
    size_t attackDamage = 0;
    size_t attackSpeed = 0;
    size_t attackRange = 0;

    size_t getHp() override {
        return hp;
    }

    int getHeal() override {
        return heal;
    }

    size_t getMoveSpeed() override {
        return moveSpeed;
    }

    size_t getAttackDamage() override {
        return attackDamage;
    }

    size_t getAttackSpeed() override {
        return attackSpeed;
    }

    size_t getAttackRange() override {
        return attackRange;
    }
};

#endif //GAME_LOCALCHARACTERSTATS_HPP
