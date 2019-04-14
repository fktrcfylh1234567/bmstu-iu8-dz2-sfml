//
// Created by fktrc on 14.04.19.
//

#include "TestClient.hpp"

void TestClient::connectToServer() {
    boost::asio::io_service io_service;
    //socket creation
    ip::tcp::socket socket(io_service);
    //connection
    socket.connect(ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
    // request/message from client
    const std::string msg1 = "Hello from Client!\n";
    boost::system::error_code error;
    boost::asio::write(socket, boost::asio::buffer(msg1), error);
    if (error) {
        std::cout << "send failed: " << error.message() << std::endl;

    }
    // getting response from server
    boost::asio::streambuf receive_buffer;
    boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
    if (error && error != boost::asio::error::eof) {
        std::cout << "receive failed: " << error.message() << std::endl;
    } else {
        const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
        std::cout << data << std::endl;
    }

}
