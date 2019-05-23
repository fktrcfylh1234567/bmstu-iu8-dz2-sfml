//
// Created by fktrc on 21.05.19.
//

#ifndef NETWORKING_CLIENT_HPP
#define NETWORKING_CLIENT_HPP

#include "ConnectionClient.hpp"

class Client {
public:
    Client(const std::string& username, const std::string& serverIp, size_t port);

    void start();
    void stop();
    bool isRunning();
    void sendMessage(const std::string& msg);
    std::string waitForMessage();

private:
    void connect();

    std::string username;
    std::string serverIP;
    size_t port;

    ConnectionClient::ptr connection;
    std::atomic_bool running;
    io_service service;
    boost::thread_group threads;
};


#endif //NETWORKING_CLIENT_HPP
