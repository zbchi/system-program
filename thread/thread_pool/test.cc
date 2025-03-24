#include "thread_pool.h"
const int SIZE = 10000;

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

    sleep(15);

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
    return 0;
}
