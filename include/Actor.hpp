//
// Created by fktrc on 08.04.19.
//

#ifndef GAME_ACTOR_HPP
#define GAME_ACTOR_HPP

#include "Entity.hpp"
#include "Buff.hpp"

class Actor : public Entity {
public:
    Actor(size_t id, Graph* gameGraph);
    void setDefaultStats(size_t hpDefault, int healDefault, size_t moveSpeedDefault, size_t damageDefault,
                         size_t attackSpeedDefault, size_t attackRangeDefault);

    void doDamage(size_t damage);
    void addBuff(Buff* buff);
    void removeBuff(Buff* buff);
    void updateBuffs();

    size_t getHp() const;
    int getHeal() const;
    size_t getMoveSpeed() const;
    size_t getDamage() const;
    size_t getAttackSpeed() const;
    size_t getAttackRange() const;
    bool isStunned() const;
    bool isImmunityFromBasicAttack() const;
    bool isImmunityFromSpells() const;

private:
    void resetAllStatsToDefault();

    size_t hpDefault;
    int healDefault;
    size_t moveSpeedDefault;

    size_t damageDefault;
    size_t attackSpeedDefault;
    size_t attackRangeDefault;

    size_t hp;
    int heal;
    size_t moveSpeed;

    size_t damage;
    size_t attackSpeed;
    size_t attackRange;

    bool stunned = false;
    bool immunityFromBasicAttack = false;
    bool immunityFromSpells = false;

    std::vector<Buff*> activeBuffs;
};


#endif //GAME_ACTOR_HPP
