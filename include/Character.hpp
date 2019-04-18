//
// Created by fktrc on 08.04.19.
//

#ifndef GAME_CHARACTER_HPP
#define GAME_CHARACTER_HPP

#include <cstdio>
#include <memory>
#include <utility>

#include "IGraph.hpp"
#include "IBuff.hpp"
#include "CharacterStatsInstance.hpp"

class Character {
public:
    Character(size_t id, std::shared_ptr<IGraph> gameGraph, const std::shared_ptr<ICharacterStats> defaulStats);

    void spawn(const Point& destination);
    void kill();

    void setPosition(const Point& destination);
    Path makePath(const Point& destination);

    bool isAlive();
    const Point& getPos() const;
    const size_t getId() const;

    void doDamage(size_t damage);
    void addBuff(std::shared_ptr<IBuff> buff);
    void removeBuff(std::shared_ptr<IBuff> buff);

    const CharacterStatsInstance& getCurrentStats() const;

private:
    const size_t id;
    std::shared_ptr<IGraph> gameGraph = nullptr;

    bool alive = false;
    Point pos = {-1, -1};

    std::shared_ptr<ICharacterStats> defaulStats = nullptr;
    CharacterStatsInstance currentStats;
    std::vector<std::shared_ptr<IBuff>> activeBuffs;

    void resetAllStatsToDefault();
    void updateBuffs();
};

#endif //GAME_CHARACTER_HPP
