//
// Created by fktrc on 20.05.19.
//

#include "Server.hpp"

void Server::start() {
    std::cout << "started" << std::endl;
    running = true;
    openLobby();
    threads.create_thread([this]() { handle_clients_thread(); })->detach();
}

void Server::stop() {
    running = false;
    lobbyOpened = false;
}

bool Server::isRunning() {
    return running;
}


void Server::openLobby() {
    if (lobbyOpened) {
        return;
    }

    std::cout << "open Lobby" << std::endl;

    lobbyOpened = true;
    threads.create_thread([this]() {
        accept_thread();
    })->detach();
}

void Server::closeLobby() {
    lobbyOpened = false;
}

bool Server::isLobbyOpened() {
    return lobbyOpened;
}


void Server::sendMessage(const std::string& msg) {
    for (std::vector<client_ptr>::iterator b = clients.begin(), e = clients.end(); b != e; ++b)
        (*b)->sendMessage(msg);
}

void Server::accept_thread() {
    ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), port));

    while (lobbyOpened) {
        client_ptr new_(new ConnectionServer(service));
        acceptor.accept(new_->sock());
        boost::recursive_mutex::scoped_lock lk(cs);
        clients.push_back(new_);
    }
}

void Server::handle_clients_thread() {
    ThreadPool pool;

    while (running) {
        boost::this_thread::sleep(millisec(1));
        boost::recursive_mutex::scoped_lock lk(cs);

        for (std::vector<client_ptr>::iterator b = clients.begin(), e = clients.end(); b != e; ++b) {
            pool.submit([b]() {
                (*b)->answer_to_client();
            });
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // erase clients that timed out
        clients.erase(std::remove_if(clients.begin(), clients.end(),
                                     boost::bind(&ConnectionServer::timed_out, _1)), clients.end());
    }
}
