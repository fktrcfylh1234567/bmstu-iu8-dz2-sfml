//
// Created by fktrc on 22.05.19.
//

#ifndef NETWORKING_THREADPOOL_HPP
#define NETWORKING_THREADPOOL_HPP

#include <future>
#include <thread>
#include <queue>
#include <functional>
#include <atomic>

class ThreadPool {
public:

    ThreadPool() {
        start();
    }

    ThreadPool(size_t num) :
            num(num) {
        start();
    }

    ~ThreadPool() {
        std::unique_lock<std::mutex> lk(mutex);
        running = false;
        lk.unlock();

        cv.notify_all();
        for (auto& t : threads)
            t.join();
    }

    template<class F, class ... Args>
    std::future<std::result_of_t<F(Args...)>> submit(F&& func, Args&& ... args) {
        using result_type = std::result_of_t<F(Args...)>;

        auto ptr_task = std::make_shared<std::packaged_task<result_type()>>(
                std::bind(std::forward<F>(func), std::forward<Args>(args)...));

        auto result = ptr_task->get_future();

        std::lock_guard<std::mutex> lk(mutex);
        tasks.emplace([ptr_task]() -> void {
            (*ptr_task)();
        });

        cv.notify_one();
        return result;
    }

private:
    void start() {
        running = true;
        for (size_t i = 0; i < num; i++)
            threads.push_back(std::thread(&ThreadPool::workingThread, this));
    }

    void workingThread() {
        while (true) {
            std::unique_lock<std::mutex> lk(mutex);
            cv.wait(lk, [this]() {
                return !running || !this->tasks.empty();
            });

            if (!running)
                return;

            auto task = tasks.front();
            tasks.pop();
            lk.unlock();

            task();
        }
    }

    size_t num = std::thread::hardware_concurrency();
    std::queue<std::function<void(void)>> tasks;
    std::vector<std::thread> threads;
    std::mutex mutex;
    std::condition_variable cv;
    bool running;
};

#endif //NETWORKING_THREADPOOL_HPP
