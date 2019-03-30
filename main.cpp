//
// Created by fktrc on 25.03.19.
//

#include "GameInstance.hpp"

int main() {
    GameInstance instance;
    instance.run();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    instance.stop();

    return 0;
}
