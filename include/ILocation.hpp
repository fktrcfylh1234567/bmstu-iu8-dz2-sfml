//
// Created by fktrc on 19.04.19.
//

#ifndef GAME_ILOCATION_HPP
#define GAME_ILOCATION_HPP

class ILocation {
public:
    virtual const std::vector<bool>& operator[](size_t id) const = 0;
};

#endif //GAME_ILOCATION_HPP
