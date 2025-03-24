#include "thread_pool.h"
threadPool::threadPool(int n)
{
    for (int i = 0; i < n; i++)
    {
        thread tmp(&threadPool::work, this);
        threads.push_back(move(tmp));
    }
}
threadPool::~threadPool()
{

    unique_lock<mutex> lock_consumer(m_consumer);
    STOP = true;
    lock_consumer.unlock();

    condition_consumer.notify_all();

    for (int i = 0; i < THREAD_NUMS; i++)
        threads[i].join();
}
void threadPool::add_task(function<void()> tmp)
{
    {
        lock_guard<mutex> lock(m_consumer);
        tasks.push(tmp);
    }
    condition_consumer.notify_one();
}
void threadPool::work()
{
    while (1)
    {

        unique_lock<mutex> lock(m_consumer);
        while (!STOP && tasks.empty())
            condition_consumer.wait(lock);
        if (STOP == true && tasks.empty())
            return;

        function<void()> task = tasks.front();
        tasks.pop();

        lock.unlock();

        task();
    }
}
