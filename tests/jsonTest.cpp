//
// Created by fktrc on 23.05.19.
//

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

using nlohmann::json;

TEST(JSON, json) {
    auto j = json::parse("[{\"eventId\":0}]");
    std::cout << j.at(0)["eventId"] << '\n';
}
