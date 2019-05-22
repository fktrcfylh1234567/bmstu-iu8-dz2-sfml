//
// Created by fktrc on 22.05.19.
//

#ifndef GAME_CHARACTER_1_HPP
#define GAME_CHARACTER_1_HPP

class character_1 :  public ICharacterStats {
public:
    size_t getHp() const override {
        return 1000;
    }

    int getHeal() const override {
        return 10;
    }

    size_t getMoveSpeed() const override {
        return 4;
    }

    size_t getAttackDamage() const override {
        return 200;
    }

    size_t getAttackSpeed() const override {
        return 3;
    }

    size_t getAttackRange() const override {
        return 1;
    }
};

#endif //GAME_CHARACTER_1_HPP
