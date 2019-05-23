//
// Created by fktrc on 23.05.19.
//

#include <iostream>
#include "Scene.hpp"

void Scene::show() {
    running = true;

    sf::RenderWindow window(sf::VideoMode(1200, 720), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen() && running) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                    std::cout << localPosition.x << " " << localPosition.y << std::endl;
                }
            }
        }



        window.clear();
        window.draw(shape);
        window.display();
    }
}

void Scene::close() {
    running = false;
}
