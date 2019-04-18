//
// Created by fktrc on 11.04.19.
//

#ifndef GAME_ICHARACTERSTATS_HPP
#define GAME_ICHARACTERSTATS_HPP

#include <cstdio>

class ICharacterStats {
public:
    virtual size_t getHp() const = 0;
    virtual int getHeal() const = 0;
    virtual size_t getMoveSpeed() const = 0;
    virtual size_t getAttackDamage() const = 0;
    virtual size_t getAttackSpeed() const = 0;
    virtual size_t getAttackRange() const = 0;
};

#endif //GAME_ICHARACTERSTATS_HPP
