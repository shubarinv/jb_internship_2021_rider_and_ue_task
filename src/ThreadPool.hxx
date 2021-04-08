//
// Created by vhundef on 08.04.2021.
//

#ifndef JB_INTSHIP_2021_THREADPOOL_HXX
#define JB_INTSHIP_2021_THREADPOOL_HXX

#include "easylogging++.h"

#include <queue>
#include <thread>
class ThreadPool {
private:
    std::vector<std::thread> workers{};

    std::queue<std::function<void()>> tasksQueue;
    bool terminateAllThreads{false};


public:
    explicit ThreadPool(unsigned int num_threads = 0) {
        if (num_threads == 0) num_threads = std::thread::hardware_concurrency();
        workers.reserve(num_threads);
        LOG(INFO) << "Threads available " << num_threads;
        for (int i = 0; i < num_threads; ++i) {
            workers.emplace_back(&ThreadPool::checkForTasks, this);
        }
    }
    std::mutex queueLock;
    void checkForTasks() {
        while (!terminateAllThreads) {
            queueLock.lock();
            LOG(INFO) << "There are " << tasksQueue.size() << " tasks left";
            queueLock.unlock();
            if (tasksQueue.empty()) {
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(100ms);

            } else {
                tasksQueue.front();
                queueLock.lock();
                tasksQueue.pop();
                queueLock.unlock();
            }
        }
    }
    void terminateThreads() {
        terminateAllThreads = true;
    }
    void addTask(const std::function<void()> &task) {
        queueLock.lock();
        tasksQueue.push(task);
        queueLock.unlock();
        LOG(INFO) << "New Task";
        //std::cout << "New Task created(" << &task << ")" << std::endl;
    }
};


#endif//JB_INTSHIP_2021_THREADPOOL_HXX
