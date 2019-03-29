//
// Created by fktrc on 26.03.19.
//

#include <Sequence.hpp>

void Sequence::Update() {

}

bool Sequence::isCanceled() const {
    return canceled;
}

size_t Sequence::getNextUpdateTime() const {
    return nextUpdateTimeMs;
}
