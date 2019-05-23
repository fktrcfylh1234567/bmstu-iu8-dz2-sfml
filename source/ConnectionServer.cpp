//
// Created by fktrc on 20.05.19.
//

#include <ConnectionServer.hpp>

std::string ConnectionServer::getUsername() const {
    return username_;
}

void ConnectionServer::answer_to_client() {
    try {
        read_request();
        process_request();
    } catch (boost::system::system_error&) {
        stop();
    }
    if (timed_out()) {
        stop();
        std::cout << "stopping " << username_ << " - no ping in time" << std::endl;
    }
}

ip::tcp::socket& ConnectionServer::sock() {
    return sock_;
}

bool ConnectionServer::timed_out() const {
    ptime now = microsec_clock::local_time();
    long long ms = (now - last_ping).total_milliseconds();
    return ms > timeout;
}

void ConnectionServer::stop() {
    boost::system::error_code err;
    sock_.close(err);
}

void ConnectionServer::sendMessage(const std::string& msg) {
    sendingQueue.push(msg);
}

void ConnectionServer::read_request() {
    if (sock_.available())
        already_read_ += sock_.read_some(
                buffer(buff_ + already_read_, max_msg - already_read_));
}

void ConnectionServer::process_request() {
    bool found_enter = std::find(buff_, buff_ + already_read_, '\n')
                       < buff_ + already_read_;

    // message is not full
    if (!found_enter)
        return;

    last_ping = microsec_clock::local_time();
    size_t pos = std::find(buff_, buff_ + already_read_, '\n') - buff_;
    std::string msg(buff_, pos);
    std::copy(buff_ + already_read_, buff_ + max_msg, buff_);
    already_read_ -= pos + 1;

    if (msg.find("login") == 0) {
        on_login(msg);
        return;
    }

    if (msg.find("ping") == 0) {
        on_ping();
        return;
    }

    on_ping();
    reseiveQueue.push(msg);
}

void ConnectionServer::on_login(const std::string& msg) {
    std::istringstream in(msg);
    in >> username_ >> username_;
    std::cout << username_ << " logged in" << std::endl;
    write("login ok\n");
}

void ConnectionServer::on_ping() {
    if (sendingQueue.empty()) {
        write("ping ok\n");
        return;
    }

    write(sendingQueue.front() + "\n");
    sendingQueue.pop();
}

void ConnectionServer::write(const std::string& msg) {
    sock_.write_some(buffer(msg));
}

std::queue<std::string>& ConnectionServer::getReseiveQueue() {
    return reseiveQueue;
}
