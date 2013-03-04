//STL���㷨ʵ�֣��󶥶ѣ�

//��������vector��ͷ�ļ���Heap��vector���洢Ԫ��
#include <vector>
#include <iostream>
#include <functional>

#define MAX_VALUE 999999 //ĳ���ܴ��ֵ�������vector�ĵ�һ��λ�ã����ѣ�

const int StartIndex = 1;//�����ж�Ԫ����ʼ����

using namespace std;

//���ඨ��
//Ĭ�ϱȽϹ���less
template <class ElemType,class Compare = less<ElemType> >
class MyHeap{
private:
	vector<ElemType> heapDataVec;//���Ԫ�ص�����
	int numCounts;//����Ԫ�ظ���
	Compare comp;//�ȽϹ���

public:
	MyHeap();

	vector<ElemType> getVec();

	void initHeap(ElemType *data,const int n);//��ʼ������
	void printfHeap();//�����Ԫ��
	void makeHeap();//����
	void sortHeap();//�������㷨
	void pushHeap(ElemType elem);//����в���Ԫ��
	void popHeap();//�Ӷ���ȡ���Ѷ���Ԫ��
	void adjustHeap(int childTree,ElemType adjustValue);//��������
	void percolateUp(int holeIndex,ElemType adjustValue);//���ݲ���
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
	//����Ԫ�����ݵ�vector��
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
	//���ѵĹ��̾���һ�����ϵ����ѵĹ��̣�ѭ�����ú���adjustHeap���ε�������
	if (numCounts < 2)
		return;
	//��һ����Ҫ�����������ĸ��ڵ����
	int parent = numCounts / 2;
	while(1)
	{
		adjustHeap(parent,heapDataVec[parent]);
		if (StartIndex == parent)//������ڵ�
			return;

		--parent;
	}
}

template <class ElemType,class Compare>
void MyHeap<ElemType,Compare>::sortHeap()
{
	//������˼·
	//ÿִ��һ��popHeap�������Ѷ���Ԫ�ر�������β�ˣ�Ȼ�����ǰ���һ����ִ��popHeap����
	//������ȥ����󼴵õ�������
	while(numCounts > 0)
		popHeap();
}

template <class ElemType,class Compare>
void MyHeap<ElemType,Compare>::pushHeap(ElemType elem)
{
	//����Ԫ����ӵ�vector��
	heapDataVec.push_back(elem);
	++numCounts;

	//ִ��һ�����ݲ����������ѣ���ʹ���������ѵ�����
	percolateUp(numCounts,heapDataVec[numCounts]);
}

template <class ElemType,class Compare>
void MyHeap<ElemType,Compare>::popHeap()
{
	//���Ѷ���Ԫ�ط�����������β����Ȼ��β����ԭԪ����Ϊ����ֵ���������ɶ�
	ElemType adjustValue = heapDataVec[numCounts];
	//�Ѷ�Ԫ��Ϊ��������Ԫ��
	heapDataVec[numCounts] = heapDataVec[StartIndex];
	//����Ԫ����Ŀ��һ
	--numCounts;

	adjustHeap(StartIndex,adjustValue);
}

//������childTreeΪ��������Ϊ��
template <class ElemType,class Compare>
void MyHeap<ElemType,Compare>::adjustHeap(int childTree,ElemType adjustValue)
{
	//���ڵ�����
	int holeIndex = childTree;
	int secondChid = 2 * holeIndex + 1;//���ڵ�����ӽڵ㣨ע�⣺��ʼ������1��ʼ��
	while(secondChid <= numCounts)
	{
		if (comp(heapDataVec[secondChid],heapDataVec[secondChid - 1]))
		{
			--secondChid;//��ʾ�����ӽڵ���ֵ�ϴ���Ǹ�
		}

		//����
		heapDataVec[holeIndex] = heapDataVec[secondChid];//��ϴ�ֵΪ��ֵ
		holeIndex = secondChid;//���ڵ���������
		secondChid = 2 * secondChid + 1;//���¼��㶴�ڵ����ӽڵ�
	}
	//������ڵ�ֻ�����ӽڵ�
	if (secondChid == numCounts + 1)
	{
		//�����ӽڵ�ֵΪ��ֵ
		heapDataVec[holeIndex] = heapDataVec[secondChid - 1];
		holeIndex = secondChid - 1;
	}
	//������ֵ���趴�ڵ�
	heapDataVec[holeIndex] = adjustValue;

	//��ʱ������δ����ѵ����ԣ���Ҫ��ִ��һ�����ݲ���
	percolateUp(holeIndex,adjustValue);
}

//���ݲ���
template <class ElemType,class Compare>
void MyHeap<ElemType,Compare>::percolateUp(int holeIndex,ElemType adjustValue)
{
	//���½ڵ����丸�ڵ���бȽϣ������ֵ���丸�ڵ�󣬾͸��ӽ���λ�á�
	//��ˣ�֪������Ҫ�Ի���ֱ�����ڵ�Ϊֹ
	int parentIndex = holeIndex / 2;
	while(holeIndex > StartIndex && comp(heapDataVec[parentIndex],adjustValue))
	{
		heapDataVec[holeIndex] = heapDataVec[parentIndex];
		holeIndex = parentIndex;
		parentIndex /= 2;
	}
	heapDataVec[holeIndex] = adjustValue;//����ֵ��������ȷ��λ��
}