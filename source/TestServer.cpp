//
// Created by fktrc on 01.04.19.
//

#include <TestServer.hpp>

void TestServer::handleRequest() {
    boost::asio::io_service io_service;

    //listen for new connection
    ip::tcp::acceptor acceptor_(io_service, ip::tcp::endpoint(ip::tcp::v4(), 1234));

    //socket creation
    ip::tcp::socket socket_(io_service);

    //waiting for connection
    acceptor_.accept(socket_);

    std::string message = read(socket_);
    std::cout << message << std::endl;
    send(socket_, "Hello From Server!");
}

std::string TestServer::read(ip::tcp::socket& socket) {
    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, "\n");
    std::string data = boost::asio::buffer_cast<const char*>(buf.data());
    return data;;
}

void TestServer::send(ip::tcp::socket& socket, const std::string& message) {
    const std::string msg = message + "\n";
    boost::asio::write(socket, boost::asio::buffer(message));
}
