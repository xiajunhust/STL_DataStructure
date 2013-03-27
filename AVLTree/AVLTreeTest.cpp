//平衡二叉树搜索树（AVL tree-Adelson-Velskii-Landis tree）编程实现
//作者：江南烟雨
//时间：2012-12-10

#include "AVLTree.h"
#include <iostream>

using namespace std;

int main()
{
	const int NumElements = 5;
	cout << "AVL树各项操作编程实现：" << endl;
	int a[NumElements] ={18,14,20,12,16};
	CAVLTree *CAVLTreeObj1 = new CAVLTree();
	CAVLTreeObj1->createAVLTree(a,NumElements);
	cout << "AVL Tree先序遍历结果：" << endl;
	CAVLTreeObj1->preOrder(CAVLTreeObj1->T);
	cout << endl;

	int insertedVal1 = 15;
	CAVLTreeObj1->T = CAVLTreeObj1->insertNode(CAVLTreeObj1->T,insertedVal1);
	cout << "向AVL树中插入元素  " << insertedVal1 << "之后的先序遍历结果：" << endl;
	CAVLTreeObj1->preOrder(CAVLTreeObj1->T);
	cout << endl;

	int insertedVal2 = 16;
	CAVLTreeObj1->T = CAVLTreeObj1->insertNode(CAVLTreeObj1->T,insertedVal2);
	cout << "向AVL树中插入元素  " << insertedVal2 << "之后的先序遍历结果：" << endl;
	CAVLTreeObj1->preOrder(CAVLTreeObj1->T);
	cout << endl;

	int minVal = CAVLTreeObj1->getMinNode(CAVLTreeObj1->T)->element;
	cout << "树中最小的元素是：" << minVal << endl;

	int maxVal = CAVLTreeObj1->getMaxNode(CAVLTreeObj1->T)->element;
	cout << "树中最大的元素是：" << maxVal << endl;

	const int deletedVal1 = 11;
	CAVLTreeObj1->T = CAVLTreeObj1->deleteNode(CAVLTreeObj1->T,deletedVal1);
	cout << "删除元素值为 " << deletedVal1 << "的节点之后的树先序遍历结果：" << endl;
	CAVLTreeObj1->preOrder(CAVLTreeObj1->T);
	cout << endl;

	const int deletedVal2 = 20;
	CAVLTreeObj1->T = CAVLTreeObj1->deleteNode(CAVLTreeObj1->T,deletedVal2);
	cout << "删除元素值为 " << deletedVal2 << "的节点之后的树先序遍历结果：" << endl;
	CAVLTreeObj1->preOrder(CAVLTreeObj1->T);
	cout << endl;

	const int deletedVal3 = 18;
	CAVLTreeObj1->T = CAVLTreeObj1->deleteNode(CAVLTreeObj1->T,deletedVal3);
	cout << "删除元素值为 " << deletedVal3 << "的节点之后的树先序遍历结果：" << endl;
	CAVLTreeObj1->preOrder(CAVLTreeObj1->T);
	cout << endl;

	const int searchedVal1 = 12;
	AVLTree searchedPNode = CAVLTreeObj1->searchNode(CAVLTreeObj1->T,searchedVal1);
	if(!searchedPNode)
		cout << "cannot find such node whose elemen equals " << searchedVal1 << endl;
	else
		cout << "search success element " << searchedVal1 << endl;

	const int searchedVal2 = 13;
	searchedPNode = CAVLTreeObj1->searchNode(CAVLTreeObj1->T,searchedVal2);
	if(!searchedPNode)
		cout << "cannot find such node whose elemen equals " << searchedVal2 << endl;
	else
		cout << "search success element " << searchedVal2 << endl;

	delete CAVLTreeObj1;

	return 0;
}
