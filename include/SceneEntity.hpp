//
// Created by fktrc on 23.05.19.
//

#ifndef GAME_SCENEENTITY_HPP
#define GAME_SCENEENTITY_HPP

#include <SFML/Graphics.hpp>

typedef std::pair<size_t, size_t> Point;

class SceneEntity {
public:
    SceneEntity(bool isFriendly, float blockSize) :
            model(blockSize / 2), friendly(isFriendly), blockSize(blockSize) {

        model.setOutlineThickness(5.f);
        model.setOutlineColor(sf::Color(250, 150, 100));

        if (friendly) {
            model.setFillColor(sf::Color::Green);
        } else {
            model.setFillColor(sf::Color::Red);
        }

    }

    bool isFriendly() const {
        return friendly;
    }

    const Point& getPos() const {
        return pos;
    }

    void setPos(Point&& pos) {
        model.setPosition(blockSize * (pos.first + 1), blockSize * (pos.second + 1));
        SceneEntity::pos = pos;
    }

    const sf::CircleShape& getModel() const {
        return model;
    }

private:
    float blockSize;
    Point pos;
    sf::CircleShape model;
    bool friendly;
};

#endif //GAME_SCENEENTITY_HPP
