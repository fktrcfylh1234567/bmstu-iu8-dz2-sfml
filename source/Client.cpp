//
// Created by fktrc on 21.05.19.
//

#include "Client.hpp"

Client::Client(const std::string& username, const std::string& serverIp, size_t port) :
        username(username), serverIP(serverIp), port(port) {}

void Client::start() {
    threads.create_thread([this]() {
        connect();
        running = false;
    })->detach();
    running = true;
}

void Client::stop() {
    connection->stop();
}

bool Client::isRunning() {
    return running;
}

void Client::sendMessage(const std::string& msg) {
    connection->sendMessage(msg);
}

std::string Client::waitForMessage() {
    return connection->getReseiveQueue().wait_and_pop();
}

void Client::connect() {
    ip::tcp::endpoint ep(ip::address::from_string(serverIP), port);
    connection = ConnectionClient::start(ep, username, service);
    service.run();
}
