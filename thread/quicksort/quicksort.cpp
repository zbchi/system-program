#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

using namespace std;

const int MAX_DEPTH = 4;

int count = 0;

vector<int> arr;

class Arr
{
public:
	Arr(vector<int> &a, int l, int h, int d) : array(a), low(l), high(h), depth(d) {}

	vector<int> &array;
	int low;
	int high;
	int depth = 0;
};

int partition(vector<int> &array, int low, int high)
{

	int pivot = array[low];
	while (low < high)
	{
		while (low < high && array[high] >= pivot)
			high--;
		array[low] = array[high];

		while (low < high && array[low] <= pivot)
			low++;
		array[high] = array[low];
	}
	array[low] = pivot;
	return low;
}

void quicksort(vector<int> &array, int low, int high)
{
	if (low < high)
	{
		int pivot = partition(array, low, high);
		quicksort(array, low, pivot - 1);
		quicksort(array, pivot + 1, high);
	}
}

void *quicksort_multipul(void *arg)
{
	Arr *tmp = (Arr *)arg;
	if (tmp->depth < MAX_DEPTH)
	{
		if (tmp->low < tmp->high)
		{
			int pivot = partition(tmp->array, tmp->low, tmp->high);

			Arr arrleft(tmp->array, tmp->low, pivot - 1, tmp->depth + 1);
			Arr arrright(tmp->array, pivot + 1, tmp->high, tmp->depth + 1);
			pthread_t left, right;
			int ret;
			ret = pthread_create(&left, NULL, quicksort_multipul, &arrleft);
			if (ret != 0)
				fprintf(stderr, "pthread_create:%s\n", strerror(ret));

			ret = pthread_create(&right, NULL, quicksort_multipul, &arrright);
			if (ret != 0)
				fprintf(stderr, "pthread_create:%s\n", strerror(ret));

			ret = pthread_join(left, NULL);
			if (ret != 0)
				fprintf(stderr, "pthread_create:%s\n", strerror(ret));
			ret = pthread_join(right, NULL);
			if (ret != 0)
				fprintf(stderr, "pthread_create:%s\n", strerror(ret));
		}
	}
	else
		quicksort(tmp->array, tmp->low, tmp->high);
	return NULL;
}

int main()
{

	int ret;

	srand(time(NULL));

	arr.reserve(100000000);
	for (int i = 0; i < 100000000; i++)
	{
		arr.push_back(rand());
	}

	Arr origin(arr, 0, 99999999, 0);
	cout << "start" << endl;

	quicksort_multipul(&origin);

	for (int i = 0; i < 100000000; i++)
		cout << arr[i] << " ";
	return 0;
}
