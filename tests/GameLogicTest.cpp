//
// Created by fktrc on 07.04.19.
//

#include <gtest/gtest.h>
#include "GameInstance.hpp"

TEST(Sequences, AddingCanceling) {
    GameInstance instance;
    size_t id1 = instance.addSequence(1, 0);
    size_t id2 = instance.addSequence(1, 0);
    size_t id3 = instance.addSequence(1, 0);
    instance.cancelSequence(id3);

    instance.updateSequences(1);

    instance.cancelSequence(id2);
    instance.updateSequences(2);

    EXPECT_EQ(id1, 1);
    EXPECT_EQ(id3, 3);
}
