//
// Created by fktrc on 19.05.19.
//

#include "Client.hpp"
#include "ThreadPool.hpp"

int main() {
    Client client("fktrc", "127.0.0.1", 8001);
    client.start();

    while (client.isRunning()) {
        std::string msg;
        std::cin >> msg;

        if (msg == "running") {
            client.stop();
            continue;
        }

        client.sendMessage(msg);
    }
}
