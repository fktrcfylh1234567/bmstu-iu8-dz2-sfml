//
// Created by fktrc on 23.05.19.
//

#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include <SceneEntity.hpp>
#include "ILevel.hpp"
#include "IPlayerAction.hpp"
#include "ConcurrentQueue.hpp"

#include <atomic>

class Scene {
public:
    void show();
    void close();

    void loadEnvironment(std::shared_ptr<ILevel> ptr);
    void addEntity(size_t entityId, bool isFriendly);

    void enableControls(size_t playerId);
    void disableControls();

private:
    void onMouseClick(sf::Vector2i& pos);

    ConcurrentQueue<std::shared_ptr<IPlayerAction>> actionsQueue;

    std::atomic_bool running = false;
    std::atomic_bool controlsEnabled = false;
    size_t playerId;

    std::shared_ptr<ILevel> level;
    std::vector<sf::RectangleShape> environment;
    std::map<size_t, SceneEntity> entities;

    const size_t locationSize = 5;
    const float blockSize = 200.f;
    const size_t screenSize = 7 * blockSize;
};

#endif //GAME_SCENE_HPP
