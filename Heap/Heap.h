//STL堆算法实现（大顶堆）

//包含容器vector的头文件：Heap用vector来存储元素
#include <vector>
#include <iostream>
#include <functional>

#define MAX_VALUE 999999 //某个很大的值，存放在vector的第一个位置（最大堆）

const int StartIndex = 1;//容器中堆元素起始索引

using namespace std;

//堆类定义
//默认比较规则less
template <class ElemType,class Compare = less<ElemType> >
class MyHeap{
private:
	vector<ElemType> heapDataVec;//存放元素的容器
	int numCounts;//堆中元素个数
	Compare comp;//比较规则

public:
	MyHeap();

	vector<ElemType> getVec();

	void initHeap(ElemType *data,const int n);//初始化操作
	void printfHeap();//输出堆元素
	void makeHeap();//建堆
	void sortHeap();//堆排序算法
	void pushHeap(ElemType elem);//向堆中插入元素
	void popHeap();//从堆中取出堆顶的元素
	void adjustHeap(int childTree,ElemType adjustValue);//调整子树
	void percolateUp(int holeIndex,ElemType adjustValue);//上溯操作
};

template <class ElemType,class Compare>
MyHeap<ElemType,Compare>::MyHeap()
:numCounts(0)
{
	heapDataVec.push_back(MAX_VALUE);
}

template <class ElemType,class Compare>
vector<ElemType> MyHeap<ElemType,Compare>::getVec()
{
	return heapDataVec;
}

template <class ElemType,class Compare>
void MyHeap<ElemType,Compare>::initHeap(ElemType *data,const int n)
{
	//拷贝元素数据到vector中
	for (int i = 0;i < n;++i)
	{
		heapDataVec.push_back(*(data + i));
		++numCounts;
	}
}

template <class ElemType,class Compare>
void MyHeap<ElemType,Compare>::printfHeap()
{
	cout << "Heap : ";
	for (int i = 1;i <= numCounts;++i)
	{
		cout << heapDataVec[i] << " ";
	}
	cout << endl;
}

template <class ElemType,class Compare>
void MyHeap<ElemType,Compare>::makeHeap()
{
	//建堆的过程就是一个不断调整堆的过程，循环调用函数adjustHeap依次调整子树
	if (numCounts < 2)
		return;
	//第一个需要调整的子树的根节点多音
	int parent = numCounts / 2;
	while(1)
	{
		adjustHeap(parent,heapDataVec[parent]);
		if (StartIndex == parent)//到达根节点
			return;

		--parent;
	}
}

template <class ElemType,class Compare>
void MyHeap<ElemType,Compare>::sortHeap()
{
	//堆排序思路
	//每执行一次popHeap操作，堆顶的元素被放置在尾端，然后针对前面的一次再执行popHeap操作
	//依次下去，最后即得到排序结果
	while(numCounts > 0)
		popHeap();
}

template <class ElemType,class Compare>
void MyHeap<ElemType,Compare>::pushHeap(ElemType elem)
{
	//将新元素添加到vector中
	heapDataVec.push_back(elem);
	++numCounts;

	//执行一次上溯操作，调整堆，以使其满足最大堆的性质
	percolateUp(numCounts,heapDataVec[numCounts]);
}

template <class ElemType,class Compare>
void MyHeap<ElemType,Compare>::popHeap()
{
	//将堆顶的元素放在容器的最尾部，然后将尾部的原元素作为调整值，重新生成堆
	ElemType adjustValue = heapDataVec[numCounts];
	//堆顶元素为容器的首元素
	heapDataVec[numCounts] = heapDataVec[StartIndex];
	//堆中元素数目减一
	--numCounts;

	adjustHeap(StartIndex,adjustValue);
}

//调整以childTree为根的子树为堆
template <class ElemType,class Compare>
void MyHeap<ElemType,Compare>::adjustHeap(int childTree,ElemType adjustValue)
{
	//洞节点索引
	int holeIndex = childTree;
	int secondChid = 2 * holeIndex + 1;//洞节点的右子节点（注意：起始索引从1开始）
	while(secondChid <= numCounts)
	{
		if (comp(heapDataVec[secondChid],heapDataVec[secondChid - 1]))
		{
			--secondChid;//表示两个子节点中值较大的那个
		}

		//上溯
		heapDataVec[holeIndex] = heapDataVec[secondChid];//令较大值为洞值
		holeIndex = secondChid;//洞节点索引下移
		secondChid = 2 * secondChid + 1;//重新计算洞节点右子节点
	}
	//如果洞节点只有左子节点
	if (secondChid == numCounts + 1)
	{
		//令左子节点值为洞值
		heapDataVec[holeIndex] = heapDataVec[secondChid - 1];
		holeIndex = secondChid - 1;
	}
	//将调整值赋予洞节点
	heapDataVec[holeIndex] = adjustValue;

	//此时可能尚未满足堆的特性，需要再执行一次上溯操作
	percolateUp(holeIndex,adjustValue);
}

//上溯操作
template <class ElemType,class Compare>
void MyHeap<ElemType,Compare>::percolateUp(int holeIndex,ElemType adjustValue)
{
	//将新节点与其父节点进行比较，如果键值比其父节点大，就父子交换位置。
	//如此，知道不需要对换或直到根节点为止
	int parentIndex = holeIndex / 2;
	while(holeIndex > StartIndex && comp(heapDataVec[parentIndex],adjustValue))
	{
		heapDataVec[holeIndex] = heapDataVec[parentIndex];
		holeIndex = parentIndex;
		parentIndex /= 2;
	}
	heapDataVec[holeIndex] = adjustValue;//将新值放置在正确的位置
}