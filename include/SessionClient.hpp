//
// Created by fktrc on 23.05.19.
//

#ifndef GAME_SESSIONCLIENT_HPP
#define GAME_SESSIONCLIENT_HPP

#include <nlohmann/json.hpp>

#include "Client.hpp"
#include "Scene.hpp"
#include "IEvent.hpp"
#include <PlayerActionMove.hpp>
#include <PlayerActionAttack.hpp>
#include "level_1.hpp"

#include <string>

using nlohmann::json;

class SessionClient {
public:
    SessionClient(const std::string& username, const std::string& serverIp, size_t port);

    void connect();
    bool isConnected();

private:
    void handleEvent(std::string msg);
    void renderScene();

    Client client;
    Scene scene;
    std::atomic_bool connected;
};

#endif //GAME_SESSIONCLIENT_HPP
