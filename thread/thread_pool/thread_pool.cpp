#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <ctime>
#include <time.h>
#include <unistd.h>
#include <vector>
#include <functional>
#include <condition_variable>
using namespace std;

queue<int> task;
class threadPool
{

public:
    threadPool(int n)
    {
        for (int i = 0; i < n; i++)
        {
            thread tmp(work);
            threads.push_back(tmp);
        }
    }

    void work()
    {
        while (1)
        {

            unique_lock<mutex> lock(m);
            while (task.empty())
            {
                cv.wait(lock);
            }
            function<void()> tmp = task.front();
            task.pop();
            lock.unlock();
            tmp();
        }
    }
    queue<function<void()>> task;
    mutex m;
    vector<thread> threads;
    condition_variable cv;
};

long long jiecheng(int n)
{
    if (n == 1)
        return 1;
    return n * jiecheng(n - 1);
}

void print()
{
    cout << "hello world" << endl;
}

void create_task()
{
    threadPool pool(10);
    while (1)
    {

        pool.task.push(print);
    }
}

void create_queue()
{
    srand(time(nullptr));

    for (int i = 0; i < 1000000000; i++)
        task.push(rand() % 20 + 1);

    cout << "----" << endl;
}

int mian()
{
    create_task();
}
