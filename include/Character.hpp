//
// Created by fktrc on 08.04.19.
//

#ifndef GAME_CHARACTER_HPP
#define GAME_CHARACTER_HPP

#include <cstdio>
#include <memory>
#include <utility>

#include "Graph.hpp"
#include "Buff.hpp"
#include "CharacterStats.hpp"

class Character {
public:
    Character(const size_t id, std::shared_ptr<Graph> gameGraph, const std::shared_ptr<CharacterStats> defaulStats);

    void spawn(const Point& destination);
    void kill();

    void setPosition(const Point& destination);
    Path makePath(const Point& destination);

    bool isAlive();
    const Point& getPos() const;
    const size_t getId() const;

    void doDamage(size_t damage);
    void addBuff(std::shared_ptr<Buff> buff);
    void removeBuff(std::shared_ptr<Buff> buff);
    void updateBuffs();

    const CharacterStats& getCurrentStats() const;
    bool isStunned() const;
    bool isImmunityFromBasicAttack() const;
    bool isImmunityFromSpells() const;

private:
    const size_t Id;
    std::shared_ptr<Graph> gameGraph;

    bool alive = false;
    Point pos = {-1, -1};

    std::shared_ptr<CharacterStats> defaulStats;
    std::unique_ptr<CharacterStats> currentStats;
    std::vector<std::shared_ptr<Buff>> activeBuffs;

    bool stunned = false;
    bool immunityFromBasicAttack = false;
    bool immunityFromSpells = false;

    void resetAllStatsToDefault();
};

#endif //GAME_CHARACTER_HPP
