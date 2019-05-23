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
}

void Scene::addEntity(size_t entityId, bool isFriendly) {
    entities.push_back(SceneEntity(entityId, blockSize, isFriendly));
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
                    size_t x = (localPosition.x / blockSize) - 1;
                    size_t y = (localPosition.y / blockSize) - 1;

                    onMouseClick({x, y});
                }
            }
        }

        window.clear();

        for (const sf::RectangleShape& rectangle : environment) {
            window.draw(rectangle);
        }

        for (const SceneEntity& entity : entities) {
            window.draw(entity.getModel());
        }

        window.display();
    }
}

void Scene::close() {
    running = false;
}

void Scene::onMouseClick(const Point& pos) {
    if (!level->getLocation()->operator[](pos.first)[pos.second]) {
        return;
    }

    std::cout << pos.first << " " << pos.second << std::endl;
}
