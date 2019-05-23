//
// Created by fktrc on 23.05.19.
//

#ifndef GAME_SESSIONCLIENT_HPP
#define GAME_SESSIONCLIENT_HPP

#include "Client.hpp"
#include "Scene.hpp"

#include <string>

class SessionClient {
public:
    SessionClient(const std::string& username, const std::string& serverIp, size_t port);

    void connect();
    bool isConnected();

private:
    void renderScene();

    Client client;
    Scene scene;
    std::atomic_bool connected;
};

#endif //GAME_SESSIONCLIENT_HPP
