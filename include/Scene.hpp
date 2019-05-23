//
// Created by fktrc on 23.05.19.
//

#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP


#include <atomic>
#include <SFML/Graphics.hpp>

class Scene {
public:
    void show();
    void close();

private:
    std::atomic_bool running = false;
};


#endif //GAME_SCENE_HPP
