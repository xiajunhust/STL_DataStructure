#include "Heap.h"

//���ȼ������ඨ��
//Ĭ�ϣ�ֵ��С��Ȩֵ���
template <class ElemType,class Compare = less<ElemType> >
class MyPriorityQueue{
private:
	MyHeap<ElemType,Compare> heap;//�ײ��ö�ʵ��

public:
	//���캯��
	MyPriorityQueue(ElemType *data,int n);

	//�ж����ȼ������Ƿ�Ϊ��
	int empty(){return heap.getVec().size() - 1;}
	//�������ȼ����д�С
	long size(){return heap.getVec().size() - 1;}//ע��ײ�������һ��Ԫ������ЧԪ��
	//ȡ�����ȼ�����ͷԪ��
	ElemType top(){return heap.getVec()[StartIndex];}
	//���Ԫ��
	void push(const ElemType &val);
	//��������Ԫ��
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
	heap.setNumCounts(heap.getVec().size() - 1);//�ų������ײ����ڱ�Ԫ��
	heap.makeHeap();
	heap.pushHeap(val);
	heap.sortHeap();
}

template <class ElemType,class Compare>
void MyPriorityQueue<ElemType,Compare>::pop()
{
	heap.getVec().erase(heap.getVec().begin() + 1);//ɾ�������ײ���Ԫ��
	heap.setNumCounts(heap.getVec().size() - 1);//�ų������ײ����ڱ�Ԫ��
	heap.makeHeap();
	heap.sortHeap();
}