//
// Created by fktrc on 14.04.19.
//

#ifndef GAME_TESTCLIENT_HPP
#define GAME_TESTCLIENT_HPP

#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;


class TestClient {
    void connectToServer();
};


#endif //GAME_TESTCLIENT_HPP
