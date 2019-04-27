//
// Created by fktrc on 27.04.19.
//

#ifndef GAME_ILEVEL_HPP
#define GAME_ILEVEL_HPP

#include <memory>
#include <utility>

#include "ILocation.hpp"
#include "IGameModeInfo.hpp"

class ILevel {
public:
    virtual const std::shared_ptr<ILocation>& getLocation() const = 0;
    virtual const std::map<size_t, std::shared_ptr<IGameModeInfo>>& getGameModesInfo() const = 0;
};

#endif //GAME_ILEVEL_HPP
