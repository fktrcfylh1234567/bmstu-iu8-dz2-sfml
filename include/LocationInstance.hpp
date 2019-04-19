//
// Created by fktrc on 19.04.19.
//

#ifndef GAME_LOCATIONINSTANCE_HPP
#define GAME_LOCATIONINSTANCE_HPP


class LocationInstance : public ILocation {
public:
    LocationInstance(const std::vector<std::vector<bool>>& level) : level(level) {}

    const std::vector<bool>& operator[](size_t id) const override {
        return level[id];
    }

private:
    std::vector<std::vector<bool>> level;
};

#endif //GAME_LOCATIONINSTANCE_HPP
