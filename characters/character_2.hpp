//
// Created by fktrc on 22.05.19.
//

#ifndef GAME_CHARACTER_2_HPP
#define GAME_CHARACTER_2_HPP


class character_2 : public ICharacterStats {
public:
    size_t getHp() const override {
        return 800;
    }

    int getHeal() const override {
        return 5;
    }

    size_t getMoveSpeed() const override {
        return 2;
    }

    size_t getAttackDamage() const override {
        return 200;
    }

    size_t getAttackSpeed() const override {
        return 5;
    }

    size_t getAttackRange() const override {
        return 3;
    }
};


#endif //GAME_CHARACTER_2_HPP
