//
// Created by fktrc on 22.05.19.
//

#include "SessionServer.hpp"

int main() {
    SessionServer gameServer;
    gameServer.setupMatch("level_1", "tdm");
    gameServer.createLobby();
    //gameServer.startMatch();

    while (gameServer.isLobbyOpened()) {
        std::string msg;
        std::cin >> msg;

        if (msg == "start") {
            gameServer.startMatch();
        }
    }

    while (gameServer.isGameRunnimg()) {
        std::string msg;
        std::cin >> msg;

        if (msg == "start") {
            gameServer.startMatch();
        }
    }
}
