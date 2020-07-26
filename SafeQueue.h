//
// Created by Dan on 7/26/2020.
//

#ifndef THREAD_SAFEQUEUE_H
#define THREAD_SAFEQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class SafeQueue {

private:
  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable cond_;

public:
    T pop();
    void push(const T& item);
    bool isEmpty();

};

template<typename T>
void SafeQueue<T>::push(const T &item) {
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push(item);
    mlock.unlock();
    cond_.notify_one();
}

template<typename T>
T SafeQueue<T>::pop() {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty())
    {
      cond_.wait(mlock);
    }
    auto item = queue_.front();
    queue_.pop();
    return item;
}

template<typename T>
bool SafeQueue<T>::isEmpty() {
    return queue_.empty();
}


#endif //THREAD_SAFEQUEUE_H
