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
private:
    std::queue<Data> the_queue;
    mutable std::mutex the_mutex;
    std::condition_variable cvar;
public:
    void push(Data const& data) {
        std::unique_lock lock(the_mutex);
        the_queue.push(data);
        lock.unlock();
        cvar.notify_one();
    }

    Data wait_and_pop() {
        std::unique_lock lock(the_mutex);
        while (the_queue.empty()) {
            cvar.wait(lock);
        }

        Data popped_value = the_queue.front();
        the_queue.pop();
        return popped_value;
    }

    bool empty() const {
        std::unique_lock lock(the_mutex);
        return the_queue.empty();
    }

    typename std::queue<Data>::size_type size() {
        std::unique_lock lock(the_mutex);
        return the_queue.size();
    }
};

#endif //GAME_CONCURRENTQUEUE_HPP
