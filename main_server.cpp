//
// Created by fktrc on 22.05.19.
//

#include "SessionServer.hpp"

int main() {
    SessionServer gameServer;
    gameServer.setupMatch("level_1", "tdm");
    gameServer.createLobby();

    while (gameServer.isLobbyOpened()) {
    }
}
