//
// Created by fktrc on 27.04.19.
//

#ifndef GAME_LEVELINSTANCE_HPP
#define GAME_LEVELINSTANCE_HPP

#include <map>
#include <memory>

#include "ILevel.hpp"

class LevelInstance : public ILevel {
public:
    const std::shared_ptr<ILocation>& getLocation() override {
        return location;
    }

    std::shared_ptr<IGameModeInfo> getGameModeInfo(size_t gameModeId) override {
        return gameModesInfo.at(gameModeId);
    }

    void setLocation(const std::shared_ptr<ILocation>& location) {
       this->location = location;
    }

    void addGameModeInfo(std::shared_ptr<IGameModeInfo> gameModeInfo) {
        this->gameModesInfo.emplace(gameModeInfo->getGameModeId(), gameModeInfo);
    }

private:
    std::shared_ptr<ILocation> location;
    std::map<size_t, std::shared_ptr<IGameModeInfo>> gameModesInfo;
};

#endif //GAME_LEVELINSTANCE_HPP
