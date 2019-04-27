//
// Created by fktrc on 29.03.19.
//

#ifndef GAME_CONCURRENTQUEUE_HPP
#define GAME_CONCURRENTQUEUE_HPP

#include <thread>
#include <mutex>
#include <future>
#include <queue>

template<typename Data>
class ConcurrentQueue {
public:
    void push(Data const& data) {
        std::unique_lock lock(mutex);
        queue.push(data);
        lock.unlock();
        cvar.notify_one();
    }

    Data wait_and_pop() {
        std::unique_lock lock(mutex);
        while (queue.empty()) {
            cvar.wait(lock);
        }

        Data popped_value = queue.front();
        queue.pop();
        return popped_value;
    }

    bool empty() const {
        std::unique_lock lock(mutex);
        return queue.empty();
    }

    typename std::queue<Data>::size_type size() {
        std::unique_lock lock(mutex);
        return queue.size();
    }

private:
    std::queue<Data> queue;
    mutable std::mutex mutex;
    std::condition_variable cvar;
};

#endif //GAME_CONCURRENTQUEUE_HPP
