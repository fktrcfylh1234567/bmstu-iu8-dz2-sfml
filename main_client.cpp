//
// Created by fktrc on 19.05.19.
//

#include <SessionClient.hpp>

int main() {
    SessionClient client("fktrc", "127.0.0.1", 8001);
    client.connect();

    while (client.isConnected()) {
    }
}
