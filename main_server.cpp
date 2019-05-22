//
// Created by fktrc on 22.05.19.
//

#include "GameServer.hpp"

int main() {
    GameServer gameServer;
    gameServer.setupMatch("level_1", "tdm");
    gameServer.createLobby();

    while (gameServer.isLobbyOpened()) {
    }
}
