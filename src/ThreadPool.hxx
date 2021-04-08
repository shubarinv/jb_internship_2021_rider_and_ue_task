//
// Created by vhundef on 08.04.2021.
//

#ifndef JB_INTSHIP_2021_THREADPOOL_HXX
#define JB_INTSHIP_2021_THREADPOOL_HXX

#include "SafeQueue.hxx"
#include "easylogging++.h"
#include <thread>
class ThreadPool {
private:
    std::vector<std::thread> workers{};

    SafeQueue<std::function<void()>> tasksQueue;
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
    void checkForTasks() {
        while (!terminateAllThreads) {
            auto ts=tasksQueue.dequeue();
            ts();
            LOG(INFO) << "Task done";
        }
    }
    void terminateThreads() {
        terminateAllThreads = true;
    }
    void addTask(const std::function<void()> &task) {
        tasksQueue.enqueue(task);
        LOG(INFO) << "New Task";
    }
    void clearQueue() {
        while (!tasksQueue.empty()) {
            tasksQueue.dequeue();
        }
    }
};


#endif//JB_INTSHIP_2021_THREADPOOL_HXX
