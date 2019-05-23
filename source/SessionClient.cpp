//
// Created by fktrc on 23.05.19.
//

#include "SessionClient.hpp"
#include "../levels/level_1.hpp"

SessionClient::SessionClient(const std::string& username, const std::string& serverIp, size_t port) :
        client(username, serverIp, port), connected(false) {
    scene.loadEnvironment(std::make_shared<level_1>());
    renderScene();
}

void SessionClient::connect() {
    connected = true;
    client.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::thread([this]() {
        while (connected) {
            std::string msg = client.waitForMessage();
            std::cout << msg << std::endl;
            //match->handleAction(playerActionFromJSON(msg));

        }
    }).detach();
}

bool SessionClient::isConnected() {
    return connected;
}

void SessionClient::renderScene() {
    std::thread([this]() {
        scene.show();
    }).detach();
}
