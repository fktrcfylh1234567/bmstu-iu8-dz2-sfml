//
// Created by fktrc on 27.04.19.
//

#ifndef GAME_LEVELINSTANCE_HPP
#define GAME_LEVELINSTANCE_HPP

#include "ILevel.hpp"

class LevelInstance : public ILevel {
public:
    const std::shared_ptr<ILocation>& getLocation() const override {
        return location;
    }

    const std::map<size_t, std::shared_ptr<IGameModeInfo>>& getGameModesInfo() const override {
        return gameModesInfo;
    }

    void setLocation(const std::shared_ptr<ILocation>& location) {
       this->location = location;
    }

    void addGameModeInfo(const std::shared_ptr<IGameModeInfo>& gameModeInfo) {
        this->gameModesInfo.emplace(gameModeInfo->getGameModeId(), gameModeInfo);
    }

private:
    std::shared_ptr<ILocation> location;
    std::map<size_t, std::shared_ptr<IGameModeInfo>> gameModesInfo;
};

#endif //GAME_LEVELINSTANCE_HPP
