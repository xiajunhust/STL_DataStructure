//ƽ���������������AVL tree-Adelson-Velskii-Landis tree�����ʵ��
//���ߣ���������
//ʱ�䣺2012-12-10

#include "AVLTree.h"
#include <iostream>

using namespace std;

int main()
{
	const int NumElements = 5;
	cout << "AVL������������ʵ�֣�" << endl;
	int a[NumElements] ={18,14,20,12,16};
	CAVLTree *CAVLTreeObj1 = new CAVLTree();
	CAVLTreeObj1->createAVLTree(a,NumElements);
	cout << "AVL Tree������������" << endl;
	CAVLTreeObj1->preOrder(CAVLTreeObj1->T);
	cout << endl;

	int insertedVal1 = 15;
	CAVLTreeObj1->T = CAVLTreeObj1->insertNode(CAVLTreeObj1->T,insertedVal1);
	cout << "��AVL���в���Ԫ��  " << insertedVal1 << "֮���������������" << endl;
	CAVLTreeObj1->preOrder(CAVLTreeObj1->T);
	cout << endl;

	int insertedVal2 = 16;
	CAVLTreeObj1->T = CAVLTreeObj1->insertNode(CAVLTreeObj1->T,insertedVal2);
	cout << "��AVL���в���Ԫ��  " << insertedVal2 << "֮���������������" << endl;
	CAVLTreeObj1->preOrder(CAVLTreeObj1->T);
	cout << endl;

	int minVal = CAVLTreeObj1->getMinNode(CAVLTreeObj1->T)->element;
	cout << "������С��Ԫ���ǣ�" << minVal << endl;

	int maxVal = CAVLTreeObj1->getMaxNode(CAVLTreeObj1->T)->element;
	cout << "��������Ԫ���ǣ�" << maxVal << endl;

	const int deletedVal1 = 11;
	CAVLTreeObj1->T = CAVLTreeObj1->deleteNode(CAVLTreeObj1->T,deletedVal1);
	cout << "ɾ��Ԫ��ֵΪ " << deletedVal1 << "�Ľڵ�֮�����������������" << endl;
	CAVLTreeObj1->preOrder(CAVLTreeObj1->T);
	cout << endl;

	const int deletedVal2 = 20;
	CAVLTreeObj1->T = CAVLTreeObj1->deleteNode(CAVLTreeObj1->T,deletedVal2);
	cout << "ɾ��Ԫ��ֵΪ " << deletedVal2 << "�Ľڵ�֮�����������������" << endl;
	CAVLTreeObj1->preOrder(CAVLTreeObj1->T);
	cout << endl;

	const int deletedVal3 = 18;
	CAVLTreeObj1->T = CAVLTreeObj1->deleteNode(CAVLTreeObj1->T,deletedVal3);
	cout << "ɾ��Ԫ��ֵΪ " << deletedVal3 << "�Ľڵ�֮�����������������" << endl;
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
