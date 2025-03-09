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
    threadPool(int n);
    ~threadPool();
    void add_task(function<void()> tmp);
    void stop();

private:
    void work();
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