#include "PriorityQueue.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
	const int n = 9;
	int data[n] = {0,1,2,3,4,8,9,3,5};
	MyPriorityQueue<int> *priorityObj1 = new MyPriorityQueue<int>(data,n);
	cout << "Current Heap: " << endl;
	for (int i = 1;i <= priorityObj1->size();++i)
	{
		cout << priorityObj1->getHeap().getVec()[i] << " ";
	}
	cout << endl;
	cout << "Size = " << priorityObj1->size() << endl;
	cout << "Top element = " << priorityObj1->top() << endl;
	priorityObj1->pop();
	cout << "After pop one element:" << endl;
	cout << "Size = " << priorityObj1->size() << endl;
	cout << "Top element = " << priorityObj1->top() << endl;

	cout << "Current Heap: " << endl;
	for (int i = 1;i <= priorityObj1->size();++i)
	{
		cout << priorityObj1->getHeap().getVec()[i] << " ";
	}
	cout << endl;

	priorityObj1->pop();
	cout << "After pop one element:" << endl;
	cout << "Size = " << priorityObj1->size() << endl;
	cout << "Top element = " << priorityObj1->top() << endl;

	cout << "Current Heap: " << endl;
	for (int i = 1;i <= priorityObj1->size();++i)
	{
		cout << priorityObj1->getHeap().getVec()[i] << " ";
	}
	cout << endl;

	priorityObj1->push(7);
	cout << "After push one element 7:" << endl;
	cout << "Size = " << priorityObj1->size() << endl;
	cout << "Top element = " << priorityObj1->top() << endl;

	cout << "Current Heap: " << endl;
	for (int i = 1;i <= priorityObj1->size();++i)
	{
		cout << priorityObj1->getHeap().getVec()[i] << " ";
	}
	cout << endl;

	delete priorityObj1;
}