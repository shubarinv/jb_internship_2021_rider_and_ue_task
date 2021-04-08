//
// Created by vhundef on 08.04.2021.
//

#ifndef JB_INTSHIP_2021_THREADPOOL_HXX
#define JB_INTSHIP_2021_THREADPOOL_HXX


#include <queue>
#include <thread>
class ThreadPool {
private:
    std::vector<std::jthread> workers{};

    std::queue<std::function<void(std::string)>>tasksQueue;
    bool terminateAllThreads{false};


public:
    explicit ThreadPool(unsigned char num_threads = 0) {
        if (num_threads == 0) num_threads = std::thread::hardware_concurrency();
        workers.reserve(num_threads);
        for (int i = 0; i < num_threads; ++i) {
         //   workers.push_back(std::jthread)
        }
    }
    void checkForTasks() {
        while (!terminateAllThreads) {
            if (tasksQueue.empty()) {
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(50ms);
            }
            else{
                tasksQueue.front();
                tasksQueue.pop();
            }
        }
    }
    void terminateThreads() {
        terminateAllThreads = true;
    }
};


#endif//JB_INTSHIP_2021_THREADPOOL_HXX
