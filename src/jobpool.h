#ifndef NC2CSV_JOBPOOL_H
#define NC2CSV_JOBPOOL_H

#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <queue>
#include "conversionjob.h"

class JobPool {
public:
    explicit JobPool(size_t _size);

    JobPool(const JobPool &other) = delete;
    JobPool &operator=(const JobPool &other) = delete;

    void run(const std::vector<std::function<void()>> &jobs);
    void run(const std::vector<ConversionJob> &jobs);

    const size_t size;
private:
    size_t running{};
    std::mutex spawn_mutex;
    std::condition_variable spawn_variable;
    std::vector<std::thread> threads;
};

#endif //NC2CSV_JOBPOOL_H
