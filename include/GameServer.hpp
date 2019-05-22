//
// Created by fktrc on 22.05.19.
//

#ifndef GAME_GAMESERVER_HPP
#define GAME_GAMESERVER_HPP

#include <Match.hpp>
#include <Server.hpp>

#include <memory>

class GameServer {
public:
    void setupMatch(std::string levelName, std::string gameModeName);
    void createLobby();
    void startMatch();
    void stopMatch();

    bool isLobbyOpened();
    bool isGameRunnimg();

private:
    std::unique_ptr<IMatch> match;
    Server server;

    std::atomic_bool lobbyOpened = false;
    std::atomic_bool gameRunnimg = false;
};

#endif //GAME_GAMESERVER_HPP
