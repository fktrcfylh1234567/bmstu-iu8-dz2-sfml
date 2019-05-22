//
// Created by fktrc on 20.05.19.
//

#ifndef NETWORKING_CONNECTIONSERVER_HPP
#define NETWORKING_CONNECTIONSERVER_HPP

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <iostream>
#include <vector>
#include <queue>

using namespace boost::asio;
using namespace boost::posix_time;

struct ConnectionServer : boost::enable_shared_from_this<ConnectionServer> {
public:
    ConnectionServer(io_service& service)
            : sock_(service), started_(false), already_read_(0) {
        last_ping = microsec_clock::local_time();
    }

    std::string getUsername() const;
    void answer_to_client();
    ip::tcp::socket& sock();
    bool timed_out() const;
    void stop();
    void sendMessage(const std::string& msg);

private:
    void read_request();
    void process_request();
    void on_login(const std::string& msg);
    void on_ping();
    void write(const std::string& msg);

    ip::tcp::socket sock_;
    enum {
        max_msg = 1024
    };
    int already_read_;
    char buff_[max_msg];
    bool started_;
    std::string username_;
    ptime last_ping;
    const size_t timeout = 200;

    std::queue<std::string> queue;
};

#endif //NETWORKING_CONNECTIONSERVER_HPP
