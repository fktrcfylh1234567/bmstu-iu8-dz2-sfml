//
// Created by fktrc on 01.04.19.
//

#ifndef GAME_TESTSERVER_HPP
#define GAME_TESTSERVER_HPP

#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;

class TestServer {
private:
    void handleRequest();
    std::string read(ip::tcp::socket& socket);
    void send(ip::tcp::socket& socket, const std::string& message);
};

#endif //GAME_TESTSERVER_HPP
