//
// Created by fktrc on 25.03.19.
//

#include "GameServer.hpp"

int main() {
    GameServer gameServer;
    gameServer.run();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    gameServer.stop();

    return 0;
}
