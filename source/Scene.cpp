//
// Created by fktrc on 23.05.19.
//

#include <iostream>
#include "Scene.hpp"

void Scene::loadEnvironment(std::shared_ptr<ILevel> ptr) {
    level = ptr;
    for (int i = 0; i < locationSize; ++i) {
        for (int j = 0; j < locationSize; ++j) {
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(blockSize, blockSize));
            rectangle.setPosition(blockSize * (i + 1), blockSize * (j + 1));

            rectangle.setOutlineThickness(2.f);
            rectangle.setOutlineColor(sf::Color(250, 150, 100));

            if (level->getLocation()->operator[](i)[j]) {
                rectangle.setFillColor(sf::Color(145, 166, 255));
            } else {
                rectangle.setFillColor(sf::Color(86, 57, 49));
            }

            environment.push_back(rectangle);
        }
    }

    addEntity(1, true);
    entities.at(1).setPos(Point(0, 0));

    addEntity(2, false);
    entities.at(2).setPos(Point(3, 4));
    entities.at(2).setHp(50);
}

void Scene::addEntity(size_t entityId, bool isFriendly) {
    entities.emplace(entityId, SceneEntity(isFriendly, blockSize));
}

void Scene::show() {
    running = true;

    sf::RenderWindow window(sf::VideoMode(screenSize, screenSize), "SFML works!");

    while (window.isOpen() && running) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                    onMouseClick(localPosition);
                }
            }
        }

        window.clear();

        for (const sf::RectangleShape& rectangle : environment) {
            window.draw(rectangle);
        }

        for (const auto& it : entities) {
            window.draw(it.second.getModel());
            window.draw(it.second.getHpIcon());
        }

        window.display();
    }
}

void Scene::close() {
    running = false;
}

void Scene::onMouseClick(sf::Vector2i& localPosition) {
    size_t x = (localPosition.x / blockSize) - 1;
    size_t y = (localPosition.y / blockSize) - 1;
    Point pos = {x, y};

    if (!level->getLocation()->operator[](pos.first)[pos.second]) {
        return;
    }

    for (const auto& it : entities) {
        if (it.second.getPos() == pos) {
            if (!it.second.isFriendly()) {
                std::cout << "attack! " << it.first << std::endl;
            }
            return;
        }
    }

    std::cout << "move " << pos.first << " " << pos.second << std::endl;
}
