#include "ThreadPool.h"
ThreadPool::ThreadPool(int threads)
{
    stop = false;
    for (int i = 0; i < threads; i++)
    {
        wokers.emplace_back(
            [this]
            {
                while (1)
                {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        condition.wait(lock, [this]
                                       { return !this->tasks.empty() || this->stop; });
                        if (this->stop && this->tasks.empty())
                            return;
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            });
    }
}

template <typename F, typename... Args>
auto ThreadPool::enqueue(F &&f, Args &...args) -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;
}
