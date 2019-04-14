//
// Created by fktrc on 11.04.19.
//

#ifndef GAME_CHARACTERSTATS_HPP
#define GAME_CHARACTERSTATS_HPP

#include <cstdio>

class CharacterStats {
public:
    virtual size_t getHp() = 0;
    virtual int getHeal() = 0;
    virtual size_t getMoveSpeed() = 0;
    virtual size_t getAttackDamage() = 0;
    virtual size_t getAttackSpeed() = 0;
    virtual size_t getAttackRange() = 0;
};

#endif //GAME_CHARACTERSTATS_HPP
