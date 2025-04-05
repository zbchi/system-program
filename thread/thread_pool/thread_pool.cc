#include "thread_pool.h"
threadPool::threadPool(int n)
{
    for (int i = 0; i < n; i++)
    {
        std::thread tmp(&threadPool::work, this);
        threads.push_back(move(tmp));
    }
}
threadPool::~threadPool()
{

    std::unique_lock<std::mutex> lock_consumer(m_consumer);
    STOP = true;
    lock_consumer.unlock();

    condition_consumer.notify_all();

    for (int i = 0; i < THREAD_NUMS; i++)
        threads[i].join();
}
void threadPool::add_task(std::function<void()> tmp)
{
    {
        std::lock_guard<std::mutex> lock(m_consumer);
        tasks.push(tmp);
    }
    condition_consumer.notify_one();
}
void threadPool::work()
{
    while (1)
    {

        std::unique_lock<std::mutex> lock(m_consumer);
        while (!STOP && tasks.empty())
            condition_consumer.wait(lock);
        if (STOP == true && tasks.empty())
            return;

        std::function<void()> task = tasks.front();
        tasks.pop();

        lock.unlock();

        task();
    }
}
