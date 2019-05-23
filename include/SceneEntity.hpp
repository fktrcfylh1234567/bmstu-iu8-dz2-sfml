//
// Created by fktrc on 23.05.19.
//

#ifndef GAME_SCENEENTITY_HPP
#define GAME_SCENEENTITY_HPP

#include <SFML/Graphics.hpp>

typedef std::pair<size_t, size_t> Point;

class SceneEntity {
public:
    SceneEntity(size_t id, float blockSize, bool isFriendly) :
            id(id), model(blockSize / 2), isFriendly(isFriendly), blockSize(blockSize) {
        if (isFriendly) {
            model.setFillColor(sf::Color::Green);
        } else {
            model.setFillColor(sf::Color::Red);
        }

        model.setOutlineThickness(5.f);
        model.setOutlineColor(sf::Color(250, 150, 100));
    }

    const Point& getPos() const {
        return pos;
    }

    void setPos(const Point& pos) {
        model.setPosition(blockSize * (pos.first + 1), blockSize * (pos.second + 1));

        SceneEntity::pos = pos;
    }

    size_t getId() const {
        return id;
    }

    const sf::CircleShape& getModel() const {
        return model;
    }

private:
    size_t id;
    float blockSize;
    Point pos;
    sf::CircleShape model;
    bool isFriendly;
};

#endif //GAME_SCENEENTITY_HPP
