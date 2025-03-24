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
    if (!has_stop)
        this->stop();
}
void threadPool::add_task(function<void()> tmp)
{
    lock_guard<mutex> lock(m_consumer);
    tasks.push(tmp);
    condition_consumer.notify_all();
}
void threadPool::work()
{
    while (1)
    {

        unique_lock<mutex> lock(m_consumer);
        if (tasks.empty())
            condition_producter.notify_all();
        while (!STOP && tasks.empty())
            condition_consumer.wait(lock);
        if (STOP == true)
            return;

        function<void()> task = tasks.front();
        tasks.pop();

        lock.unlock();

        task();
    }
}

void threadPool::stop()
{
    unique_lock<mutex> lock_productor(m_productor);
    while (!tasks.empty())
        condition_producter.wait(lock_productor);

    unique_lock<mutex> lock_consumer(m_consumer);
    STOP = true;
    lock_consumer.unlock();

    condition_consumer.notify_all();

    for (int i = 0; i < THREAD_NUMS; i++)
        threads[i].join();

    has_stop = true;
}
