//
// Created by fktrc on 20.05.19.
//

#include "ConnectionClient.hpp"

void ConnectionClient::stop() {
    if (!started) return;
    std::cout << "stopping " << username << std::endl;
    started = false;
    sock.close();
}

bool ConnectionClient::isStarted() {
    return started;
}

void ConnectionClient::sendMessage(const std::string& msg) {
    sendingQueue.push(msg);
}

ConcurrentQueue<std::string>& ConnectionClient::getReseiveQueue() {
    return reseiveQueue;
}

void ConnectionClient::on_connect(const ConnectionClient::error_code& err) {
    if (!err) do_write("login " + username + "\n");
    else stop();
}

void ConnectionClient::on_read(const ConnectionClient::error_code& err, size_t bytes) {
    if (err) stop();
    if (!isStarted()) return;

    std::string msg(read_buffer, bytes);

    if (msg.find("login") == 0) {
        on_login();
        return;
    }

    if (msg.find("ping") == 0) {
        on_ping();
        return;
    }

    postpone_ping();
    //std::cout << msg << std::endl;
    reseiveQueue.push(msg);
}

void ConnectionClient::on_login() {
    std::cout << username << " logged in" << std::endl;
    postpone_ping();
}

void ConnectionClient::on_ping() {
    postpone_ping();
}

void ConnectionClient::on_write(const ConnectionClient::error_code& err, size_t bytes) {
    do_read();
}

void ConnectionClient::do_ping() {
    if (sendingQueue.empty()) {
        do_write("ping\n");
        return;
    }

    do_write(sendingQueue.front() + "\n");
    sendingQueue.pop();
}

void ConnectionClient::do_read() {
    async_read(sock, buffer(read_buffer),
               boost::bind(&self_type::read_complete, shared_from_this(), _1, _2),
               boost::bind(&self_type::on_read, shared_from_this(), _1, _2));
}

void ConnectionClient::do_write(const std::string& msg) {
    if (!isStarted()) return;
    std::copy(msg.begin(), msg.end(), write_buffer);
    sock.async_write_some(buffer(write_buffer, msg.size()),
                          boost::bind(&self_type::on_write, shared_from_this(), _1, _2));
}

void ConnectionClient::postpone_ping() {
    timer.expires_from_now(boost::posix_time::millisec(pingRate));
    timer.async_wait(boost::bind(&self_type::do_ping, shared_from_this()));
}

size_t ConnectionClient::read_complete(const boost::system::error_code& err, size_t bytes) {
    if (err) return 0;
    bool found = std::find(read_buffer, read_buffer + bytes, '\n') < read_buffer + bytes;
    return found ? 0 : 1;
}
