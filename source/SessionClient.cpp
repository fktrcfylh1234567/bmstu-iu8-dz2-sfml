//
// Created by fktrc on 23.05.19.
//

#include "SessionClient.hpp"
#include "../levels/level_1.hpp"

SessionClient::SessionClient(const std::string& username, const std::string& serverIp, size_t port) :
        client(username, serverIp, port), connected(false) {
    scene.loadEnvironment(std::make_shared<level_1>());
}

void SessionClient::connect() {
    connected = true;
    client.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::thread([this]() {
        while (connected) {
            std::string msg = client.waitForMessage();
            std::cout << msg << std::endl;
            handleEvent(msg);
        }
    }).detach();
}

bool SessionClient::isConnected() {
    return connected;
}

void SessionClient::handleEvent(std::string msg) {
    auto j = json::parse(msg);

    for (size_t i = 0; i < j.size(); i++) {
        std::cout << j.at(i)["eventId"] << std::endl;

        if (j.at(i)["eventId"] == GAME_EVENT_MATCH_START) {
            renderScene();
            scene.enableControls(1);
        }
    }
}

void SessionClient::renderScene() {
    std::thread([this]() {
        scene.show();
    }).detach();
}
