//
// Created by fktrc on 11.04.19.
//

#ifndef GAME_CHARACTERSTATS_HPP
#define GAME_CHARACTERSTATS_HPP

#include <cstdio>

class CharacterStats {
public:
    virtual size_t getHp() const = 0;
    virtual int getHeal() const = 0;
    virtual size_t getMoveSpeed() const = 0;
    virtual size_t getAttackDamage() const = 0;
    virtual size_t getAttackSpeed() const = 0;
    virtual size_t getAttackRange() const = 0;
};

#endif //GAME_CHARACTERSTATS_HPP
