#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>

class ThreadPool
{
public:
    ThreadPool(int n);
    ~ThreadPool();
    template <typename F, typename... Args>
    auto enqueue(F &&f, Args &...args) -> std::future<typename std::result_of<F(Args...)>::type>;

private:
    std::vector<std::thread> wokers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};