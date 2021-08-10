#include "jobpool.h"
#include <chrono>

JobPool::JobPool(size_t _size) : size(_size) { }

void JobPool::run(const std::vector<std::function<void()>> &jobs) {
    for (auto &fn : jobs) {
        std::unique_lock<std::mutex> spawn_lock(spawn_mutex);
        spawn_variable.wait(spawn_lock, [this] { return running < size; });
        running++;

        threads.emplace_back([&fn, this] {
            fn();

            std::lock_guard<std::mutex> spawn_lock(spawn_mutex);
            running--;
            spawn_variable.notify_one();
        });
    }

    for (auto &thread : threads) {
        thread.join();
    }
}

void JobPool::run(const std::vector<ConversionJob> &jobs) {
    std::vector<std::function<void()>> fns;
    fns.reserve(jobs.size());
    for (auto &job : jobs) {
        fns.push_back(job.get_function());
    }
    run(fns);
}
