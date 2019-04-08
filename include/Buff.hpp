//
// Created by fktrc on 08.04.19.
//

#ifndef GAME_BUFF_HPP
#define GAME_BUFF_HPP

#include <cstdio>

class Buff {
public:
    // Numerical
    int heal = 0;
    size_t damage = 0;
    size_t attackRange = 0;

    // Coefficents
    float moveSpeed = 1;
    float attackSpeed = 1;

    // Flags
    bool stunned = false;
    bool immunityFromBasicAttack = false;
    bool immunityFromSpells = false;
};


#endif //GAME_BUFF_HPP
