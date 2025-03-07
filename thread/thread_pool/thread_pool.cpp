#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <vector>
#include <functional>
#include <condition_variable>
#include <atomic>
#include <string>
using namespace std;
const int SIZE = 10000;
const int THREAD_NUMS = 16;

class threadPool
{

public:
    threadPool(int n)
    {
        for (int i = 0; i < n; i++)
        {
            thread tmp(&threadPool::work, this);
            threads.push_back(move(tmp));
        }
    }
    ~threadPool()
    {
        if (!has_stop)
            this->stop();
    }
    void add_task(function<void()> tmp)
    {
        lock_guard<mutex> lock(m_consumer);
        tasks.push(tmp);
        condition_consumer.notify_all();
    }
    void work()
    {
        while (1)
        {

            unique_lock<mutex> lock(m_consumer);
            if (tasks.empty() && threads_active == 0)
            {
                condition_producter.notify_all();
                // cout << "notice producer" << endl;
            }
            while (!STOP && tasks.empty())
            {
                // 此处阻塞
                condition_consumer.wait(lock);
            }
            if (STOP == true)
            {
                // cout << "i am thread,exited" << endl;
                return;
            }

            function<void()> task = tasks.front();
            tasks.pop();

            threads_active++;
            lock.unlock();

            task();

            lock.lock();
            threads_active--;
            lock.unlock();
        }
    }

    void stop()
    {
        unique_lock<mutex> lock_productor(m_productor);
        while (!tasks.empty() || threads_active != 0)
        {
            // 此处阻塞
            condition_producter.wait(lock_productor);
        }

        unique_lock<mutex> lock_consumer(m_consumer);
        STOP = true;
        lock_consumer.unlock();

        condition_consumer.notify_all();

        for (int i = 0; i < THREAD_NUMS; i++)
        {
            threads[i].join();
        }

        has_stop = true;
    }

private:
    queue<function<void()>> tasks;
    mutex m_consumer;
    mutex m_productor;
    vector<thread> threads;
    condition_variable condition_consumer;
    condition_variable condition_producter;
    int threads_active = 0;
    bool STOP = false;
    bool has_stop = false;
};

vector<int> caculate_factorial(int n)
{
    vector<int> result;
    result.reserve(3000);
    result.push_back(1);

    for (int i = 2; i <= n; i++)
    {

        int carry = 0;
        for (size_t j = 0; j < result.size(); j++)
        {
            int product = result[j] * i + carry;
            result[j] = product % 10;
            carry = product / 10;
        }

        while (carry > 0)
        {
            result.push_back(carry % 10);
            carry /= 10;
        }
    }

    return result;
}

void create_tasks()
{
    srand(time(NULL));
    threadPool pool(THREAD_NUMS);

    for (int i = 0; i < SIZE; i++)
    {
        pool.add_task([]()
                      {
                          vector<int> result;
                          result.reserve(3000);
                          result = caculate_factorial(1000);
                          string str;
                          for (int i = result.size()-1; i > 0; i--)
                          str+=(char)(result[i]+'0');
                          printf("%s\n",str.c_str()); });
    }
    // pool.stop();
}

int main()
{

    /*for (int i = 0; i < SIZE; i++)
    {
        auto lambda = ([]()
                       {
        vector<int>result;
        result.reserve(3000);
        result=caculate_factorial(rand()%1000+1);
        for(int i=result.size();i>0;i--)
        cout<<result[i];
        cout<<endl; });
        lambda();
    }*/

    create_tasks();

    // cout << "thread pool exited in main" << endl;
    return 0;
}
