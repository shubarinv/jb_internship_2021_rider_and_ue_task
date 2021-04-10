//
// Created by vhundef on 08.04.2021.
//

#ifndef JB_INTSHIP_2021_THREADPOOL_HXX
#define JB_INTSHIP_2021_THREADPOOL_HXX

#include "SafeQueue.hxx"
#include <spdlog/spdlog.h>
#include <thread>
class ThreadPool {
private:
    std::vector<std::thread> workers{};
    mutable std::mutex m;
    SafeQueue<std::function<void()>> tasksQueue;
    bool terminateAllThreads{false};


public:
    explicit ThreadPool(unsigned int num_threads = 0) {
        if (num_threads == 0) num_threads = std::thread::hardware_concurrency();
        workers.reserve(num_threads);
        spdlog::info("Threads available {}", num_threads);
        for (int i = 0; i < num_threads; ++i) {
            workers.emplace_back(&ThreadPool::checkForTasks, this);
        }
    }
    void checkForTasks() {
        while (!terminateAllThreads) {
            if (m.try_lock()) {
                if (tasksQueue.empty()) {
                    m.unlock();
                    spdlog::info("No tasks");
                    using namespace std::chrono_literals;
                    std::this_thread::sleep_for(1ms);
                    continue;
                }
                m.unlock();
            }
            else{continue;}
            std::function<void()> task;
            if (m.try_lock()) {
                task = tasksQueue.dequeue();
                m.unlock();
                spdlog::info("Task assigned!");
            } else {
                spdlog::info("Mutex locked waiting");

                //    std::this_thread::sleep_for(1ms);
                continue;
            }
            task();
            spdlog::info("Task done!");
        }
    }
    void terminateThreads() {
        terminateAllThreads = true;
    }
    void addTask(const std::function<void()> &task) {
        while(!m.try_lock()){
            spdlog::info("ThreadPool::addTask mutex locked. waiting...");
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1ms);
        }
        tasksQueue.enqueue(task);
        m.unlock();
        spdlog::info("ThreadPool::addTask New task created");
    }
    void clearQueue() {
        while(!m.try_lock()){
            spdlog::info("ThreadPool::clearQueue mutex locked. waiting...");
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1ms);
        }
        while (!tasksQueue.empty()) {
            tasksQueue.dequeue();
        }
        m.unlock();
    }
};


#endif//JB_INTSHIP_2021_THREADPOOL_HXX
