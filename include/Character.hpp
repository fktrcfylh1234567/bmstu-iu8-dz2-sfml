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
#include "InstanceCharacterStats.hpp"

class Character {
public:
    Character(size_t id, std::shared_ptr<Graph> gameGraph, const std::shared_ptr<CharacterStats> defaulStats);

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

    const InstanceCharacterStats& getCurrentStats() const;

private:
    const size_t id;
    std::shared_ptr<Graph> gameGraph = nullptr;

    bool alive = false;
    Point pos = {-1, -1};

    std::shared_ptr<CharacterStats> defaulStats = nullptr;
    InstanceCharacterStats currentStats;
    std::vector<std::shared_ptr<Buff>> activeBuffs;

    void resetAllStatsToDefault();
    void updateBuffs();
};

#endif //GAME_CHARACTER_HPP
