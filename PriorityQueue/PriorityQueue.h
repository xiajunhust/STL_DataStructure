#include "Heap.h"

//优先级队列类定义
//默认：值最小的权值最大
template <class ElemType,class Compare = less<ElemType> >
class MyPriorityQueue{
private:
	MyHeap<ElemType,Compare> heap;//底层用堆实现

public:
	//构造函数
	MyPriorityQueue(ElemType *data,int n);

	//判断优先级队列是否为空
	int empty(){return heap.getVec().size() - 1;}
	//返回优先级队列大小
	long size(){return heap.getVec().size() - 1;}//注意底层容器第一个元素是无效元素
	//取得优先级队列头元素
	ElemType top(){return heap.getVec()[StartIndex];}
	//添加元素
	void push(const ElemType &val);
	//弹出队首元素
	void pop();
	MyHeap<ElemType,Compare>& getHeap(){return heap;};
};

template <class ElemType,class Compare>
MyPriorityQueue<ElemType,Compare>::MyPriorityQueue(ElemType *data, int n)
{
	heap.initHeap(data,n);
	heap.makeHeap();
	heap.sortHeap();
}

template <class ElemType,class Compare>
void MyPriorityQueue<ElemType,Compare>::push(const ElemType &val)
{
	heap.setNumCounts(heap.getVec().size() - 1);//排除容器首部的哨兵元素
	heap.makeHeap();
	heap.pushHeap(val);
	heap.sortHeap();
}

template <class ElemType,class Compare>
void MyPriorityQueue<ElemType,Compare>::pop()
{
	heap.getVec().erase(heap.getVec().begin() + 1);//删除队列首部的元素
	heap.setNumCounts(heap.getVec().size() - 1);//排除容器首部的哨兵元素
	heap.makeHeap();
	heap.sortHeap();
}