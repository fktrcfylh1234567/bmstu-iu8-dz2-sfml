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
    const std::shared_ptr<ILocation>& getLocation() const override {
        return location;
    }

    const std::shared_ptr<ILevelGameModeInfo> getGameModesInfo(size_t gameModeId) const override {
        return gameModesInfo[gameModeId];
    }

    void setLocation(const std::shared_ptr<ILocation>& location) {
       this->location = location;
    }

    void addGameModeInfo(const std::shared_ptr<ILevelGameModeInfo>& gameModeInfo, size_t gameModeId) {
        this->gameModesInfo.emplace(gameModeId, gameModeInfo);
    }

private:
    std::shared_ptr<ILocation> location;
    std::map<size_t, std::shared_ptr<ILevelGameModeInfo>> gameModesInfo;
};

#endif //GAME_LEVELINSTANCE_HPP
