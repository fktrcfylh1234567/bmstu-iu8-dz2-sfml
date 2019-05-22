//
// Created by fktrc on 22.05.19.
//

#include "GameServer.hpp"

void GameServer::setupMatch(std::string levelName, std::string gameModeName) {
    match = std::make_unique<Match>();

    size_t gameModeId = 1;

    if (gameModeName == "tdm") {
        gameModeId = 1;
    }

    match->setupGame(levelName, gameModeId);
}

void GameServer::createLobby() {
    lobbyOpened = true;
    server.start();
}

void GameServer::startMatch() {
    lobbyOpened = false;
    gameRunnimg = true;

    match->run();
    server.closeLobby();
}

void GameServer::stopMatch() {
    gameRunnimg = false;

    match->stop();
    server.stop();
}

bool GameServer::isLobbyOpened() {
    return lobbyOpened;
}

bool GameServer::isGameRunnimg() {
    return gameRunnimg;
}
