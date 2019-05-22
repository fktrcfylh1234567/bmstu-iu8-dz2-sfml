//
// Created by fktrc on 20.05.19.
//

#ifndef NETWORKING_SERVER_HPP
#define NETWORKING_SERVER_HPP

#include <ConnectionServer.hpp>
#include <ThreadPool.hpp>

typedef boost::shared_ptr<ConnectionServer> client_ptr;

class Server {
public:
    void start();
    void stop();
    bool isRunning();

    void openLobby();
    void closeLobby();
    bool isLobbyOpened();

    void sendMessage(const std::string& msg);

private:
    void accept_thread();
    void handle_clients_thread();

    std::atomic_bool running = false;
    std::atomic_bool lobbyOpened = false;

    io_service service;
    boost::thread_group threads;
    std::vector<client_ptr> clients;
    boost::recursive_mutex cs;

    const size_t port = 8001;
};

#endif //NETWORKING_SERVER_HPP
