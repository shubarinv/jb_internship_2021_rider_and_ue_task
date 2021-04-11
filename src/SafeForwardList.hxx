//
// Created by vhund on 11.04.2021.
//

#ifndef JB_INTSHIP_2021_SAFEFORWARDLIST_HXX
#define JB_INTSHIP_2021_SAFEFORWARDLIST_HXX


#include <condition_variable>
#include <list>
#include <mutex>
template<class T>
class SafeList {
public:
    SafeList() : list(), m(), c() {}

    ~SafeList() {}

    // Add an element to the queue.
    void push_back(T t) {
        std::lock_guard<std::mutex> lock(m);
        list.push_back(t);
        c.notify_one();
    }

    // Get the front element.
    // If the queue is empty, wait till a element is avaiable.
    T dequeue() {
        std::unique_lock<std::mutex> lock(m);
        while (list.empty()) {
            // release lock as long as the wait and reaquire it afterwards.
            c.wait(lock);
        }
        T val = list.back();
        list.pop_back();
        return val;
    }
    bool empty() {
        std::unique_lock<std::mutex> lock(m);
        return list.empty();
    }


private:
    std::list<T> list;
    mutable std::mutex m;
    std::condition_variable c;
};


#endif//JB_INTSHIP_2021_SAFEFORWARDLIST_HXX
