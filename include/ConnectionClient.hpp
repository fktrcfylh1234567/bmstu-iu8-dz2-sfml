//
// Created by fktrc on 20.05.19.
//

#ifndef NETWORKING_CONNECTIONCLIENT_HPP
#define NETWORKING_CONNECTIONCLIENT_HPP

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <iostream>
#include <queue>

using namespace boost::asio;

class ConnectionClient : public boost::enable_shared_from_this<ConnectionClient>, boost::noncopyable {
private:
    typedef ConnectionClient self_type;

    ConnectionClient(const std::string& username, io_service& service)
            : sock(service), started(true), username(username), timer(service) {}

    void start(ip::tcp::endpoint ep) {
        sock.async_connect(ep, boost::bind(&self_type::on_connect, shared_from_this(), _1));
    }

public:
    typedef boost::system::error_code error_code;
    typedef boost::shared_ptr<ConnectionClient> ptr;

    static ptr start(ip::tcp::endpoint ep, const std::string& username, io_service& service) {
        ptr new_(new ConnectionClient(username, service));
        new_->start(ep);
        return new_;
    }

    void stop();
    bool isStarted();
    void sendMessage(const std::string& msg);

private:
    void on_connect(const error_code& err);
    void on_read(const error_code& err, size_t bytes);
    void on_login();
    void on_ping();
    void on_write(const error_code& err, size_t bytes);

    void do_ping();
    void do_read();
    void do_write(const std::string& msg);

    void postpone_ping();
    size_t read_complete(const boost::system::error_code& err, size_t bytes);

    ip::tcp::socket sock;
    enum {
        max_msg = 1024
    };
    char read_buffer[max_msg];
    char write_buffer[max_msg];
    bool started;
    std::string username;
    deadline_timer timer;
    const size_t pingRate = 10;

    std::queue<std::string> queue;
};

#endif //NETWORKING_CONNECTIONCLIENT_HPP
