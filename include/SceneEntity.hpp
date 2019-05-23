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

        hpIcon.setSize(sf::Vector2f(blockSize * hp / 100, 10.f));
        hpIcon.setFillColor(sf::Color::Magenta);
        hpIcon.setOutlineThickness(1.f);
        hpIcon.setOutlineColor(sf::Color(250, 150, 100));
    }

    bool isFriendly() const {
        return friendly;
    }

    const Point& getPos() const {
        return pos;
    }

    void setPos(const Point& pos) {
        model.setPosition(blockSize * (pos.first + 1), blockSize * (pos.second + 1));
        hpIcon.setPosition(blockSize * (pos.first + 1), blockSize * (pos.second + 1) - blockSize * 0.1);
        this->pos = pos;
    }

    float getHp() const {
        return hp;
    }

    void setHp(float hp) {
        this->hp = hp;
        hpIcon.setSize(sf::Vector2f(blockSize * hp / 100, 10.f));
    }

    const sf::CircleShape& getModel() const {
        return model;
    }

    const sf::RectangleShape& getHpIcon() const {
        return hpIcon;
    }

private:
    sf::CircleShape model;
    sf::RectangleShape hpIcon;

    float blockSize;
    Point pos;
    bool friendly;
    float hp = 100;
};

#endif //GAME_SCENEENTITY_HPP
