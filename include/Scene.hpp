//
// Created by fktrc on 23.05.19.
//

#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP


#include <atomic>
#include <SceneEntity.hpp>
#include "ILevel.hpp"



class Scene {
public:
    void loadEnvironment(std::shared_ptr<ILevel> ptr);
    void addEntity(size_t entityId, bool isFriendly);

    void show();
    void close();

private:
    void onMouseClick(const Point& pos);

    std::atomic_bool running = false;
    std::shared_ptr<ILevel> level;
    std::vector<sf::RectangleShape> environment;
    std::vector<SceneEntity> entities;

    const size_t locationSize = 5;
    const float blockSize = 200.f;
    const float characterSize = 50.f;
    const size_t screenSize = 7 * blockSize;
};

#endif //GAME_SCENE_HPP
