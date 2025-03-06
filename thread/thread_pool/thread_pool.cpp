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
const int SIZE = 10000;

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

    void add_task(function<void()> tmp)
    {
        lock_guard<mutex> lock(m);
        tasks.push(tmp);
        cv.notify_all();
    }
    void work()
    {
        while (1)
        {
            usleep(10);
            unique_lock<mutex> lock(m);
            while (tasks.empty())
            {
                cv.wait(lock);
            }
            function<void()> tmp = tasks.front();
            tasks.pop();
            lock.unlock();
            tmp();
        }
    }
    queue<function<void()>> tasks;
    mutex m;
    vector<thread> threads;
    condition_variable cv;
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
    threadPool pool(16);

    for (int i = 0; i < SIZE; i++)
    {
        pool.add_task([]()
                      {
                          vector<int> result;
                          result.reserve(3000);
                          result = caculate_factorial(1000);
                           for (int i = result.size(); i > 0; i--)
                            cout<<result[i];
                           cout<<endl; });
    }
    sleep(1);
}

int main()
{
    srand(time(NULL));

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
    sleep(100);
    return 0;
}
