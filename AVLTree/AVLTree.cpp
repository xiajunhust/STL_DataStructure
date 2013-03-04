#include "AVLTree.h"

#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

CAVLTree::CAVLTree()
{
	T = NULL;
}

CAVLTree::~CAVLTree()
{
	if(T)
	{
		if(NULL == T->left && NULL == T->right)
			delete T;
		else{
			delete T->left;
			delete T->right;
		}
	}
}

//���ݸ�Ԫ�ص�����ֵ������AVL��
void CAVLTree::createAVLTree(ElementType *data,int n)
{
	if (T)
	{
		cout << "The AVL Tree has been created" << endl;

		return;
	}

	if(!n)//Ԫ������Ϊ��
	{
		T = NULL;
		return;
	}

	for(int i = 0;i < n;++i)
	{
		T = insertNode(T,*(data + i));
	}

	return;
}

AVLTree CAVLTree::insertNode(AVLTree T,ElementType val)
{
	AVLNode *pNewNode = new AVLNode;
	pNewNode->element = val;
	pNewNode->left = NULL;
	pNewNode->right = NULL;
	pNewNode->height = 1;//�½ڵ�һ���������ڿսڵ��λ��

	if(NULL == T)
	{
		T = pNewNode;
		return T;
	}

	//��Ҫ����ڵ�����ǿ�
	//�����Ԫ���Ѿ����������У�������Ҫ��
	if (val == T->element)
	{
		cout << "Ԫ�������ظ�������AVL��ʧ�ܣ�" << endl;
		return T;
	}
	//Ҫ�����ֵС�ڸ��ڵ��ֵ�����������������
	if(val < T->element)
	{
		//���������ڵ����������
		T->left = insertNode(T->left,val);
		//�ж�ƽ�������Ƿ���Ȼ����
		if(getHeight(T->left) - getHeight(T->right) > 1)
		{
			//���������������ת����
			//�����λ��T�����ӽ���������
			if(val < T->left->element)
				//ʵʩ����ת-����ת
				T = SingleRightRotate(T);
			else
				//�����λ��T�����ӽ�����������ʵʩ˫����ת
				T = DoubleRightRotate(T);
		}
	}
	//Ҫ�����ֵ���ڸ��ڵ��ֵ�����������������
	if(val > T->element)
	{
		T->right = insertNode(T->right,val);
		//�ж�ƽ�������Ƿ���Ȼ����
		if(getHeight(T->right) - getHeight(T->left) > 1)
		{
			//�ڵ���뵽T�����ӽڵ����������
			if(val > T->right->element)
				//ʵʩ����ת-����ת
				T = SingleLeftRotate(T->right);
			else
				//�ڵ���뵽T�����ӽڵ����������
				//ʵʩ˫��ת-����ת
				T = DoubleLeftRotate(T);
		}
	}

	//���½ڵ��heightֵ
	setHeight(T,max(getHeight(T->left),getHeight(T->right)) + 1);

	return T;
}

AVLTree CAVLTree::deleteNode(AVLTree T,const ElementType val)
{
	if (!T)
	{
		cout << "The tree is NULL, delete failed" << endl;
		return T;
	}

	AVLTree searchedNode = searchNode(T,val);
	//û���ҵ���Ӧ�Ľڵ㣬ɾ��ʧ��
	if (!searchedNode)
	{
		cout << "Cann't find the node whose element equals " << val << endl;
		return T;
	} 
	
	//�ҵ�����Ҫɾ���Ľڵ�
	//��Ҫɾ���Ľڵ���ǵ�ǰ�����ĸ��ڵ�
	if (val == T->element)
	{
		//�����������ǿ�
		if (T->left && T->right)
		{
			//�ڸ߶ȸ�����Ǹ������Ͻ���ɾ������
			if (getHeight(T->left) > getHeight(T->right))
			{
				//�������߶ȴ�ɾ����������Ԫ��ֵ�����Ǹ��ڵ�
				T->element = getMaxNode(T->left)->element;
				T->left = deleteNode(T->left,T->element);
			}
			else{
				//ɾ����������Ԫ��ֵ��С���Ǹ��ڵ�
				T->element = getMinNode(T->right)->element;
				T->right = deleteNode(T->right,T->element);
			}
		}
		else{
			//������������һ����Ϊ�գ��Ǹ�ֱ������Ҫ��ɾ���Ľڵ���ӽڵ��滻֮����
			AVLTree oldNode = T;
			T = (T->left ? T->left : T->right);
			delete oldNode;//�ͷŽڵ���ռ�Ŀռ�
		}
	}
	else if (val < T->element)//Ҫɾ���Ľڵ�����������
	{
		//���������н���ɾ��
		T->left = deleteNode(T->left,val);
		//�ж��Ƿ���Ȼ����ƽ������
		if (getHeight(T->right) - getHeight(T->left) > 1)
		{
			if (T->right->left > T->right->right)
			{
				//��˫��ת
				T = DoubleLeftRotate(T);
			}
			else//��������ת
				T = SingleLeftRotate(T);
		}
		else
			//����ƽ����������Ҫ���¸߶���Ϣ
			T->height = max(getHeight(T->left),getHeight(T->right)) + 1;
	}
	else//��Ҫɾ���Ľڵ�����������
	{
		T->right = deleteNode(T->right,val);
		//�ж��Ƿ�����ƽ������
		if (getHeight(T->left) - getHeight(T->right) > 1)
		{
			if(getHeight(T->left->right) > getHeight(T->left->left))
				//��˫��ת
				T = DoubleRightRotate(T);
			else
				//�ҵ���ת
				T = SingleRightRotate(T);
		}
		else
			//ֻ������߶ȼ���
			T->height = max(getHeight(T->left),getHeight(T->right)) + 1;
	}

	return T;
}

AVLTree CAVLTree::searchNode(AVLTree T,ElementType val)
{
	if (!T)
	{
		return NULL;
	}

	//������
	if (val == T->element)
	{
		return T;
	}
	else if (val < T->element)
	{
		//��������������
		return searchNode(T->left,val);
	}
	else
	{
		//��������������
		return searchNode(T->right,val);
	}
}

void CAVLTree::preOrder(AVLTree T)
{
	if(!T)
		cout << "NULL ";
	else
	{
		cout << T->element << " ";
		preOrder(T->left);
		preOrder(T->right);
	}
}

AVLTree CAVLTree::getMaxNode(AVLTree T)
{
	if (!T)//��Ϊ��
	{
		return NULL;
	}

	AVLTree tempNode = T;
	//������Ѱֱ�����ӽڵ�ΪNULL
	while(tempNode->right)
	{
		tempNode = tempNode->right;
	}

	return tempNode;
}

AVLTree CAVLTree::getMinNode(AVLTree T)
{
	if (!T)//��Ϊ��
	{
		return NULL;
	}

	AVLTree tempNode = T;
	//������Ѱֱ�����ӽ��ΪNULL
	while(tempNode->left)
	{
		tempNode = tempNode->left;
	}

	return tempNode;
}

int CAVLTree::getHeight(AVLTree T)
{
	return (T == NULL) ? 0 : (T->height);
}

void CAVLTree::setHeight(AVLTree T,int height)
{
	T->height = height;
}

//���������뵼�µĲ�ƽ�⣬���õ���ת-����ת��������
//�������ͣ�
//T��ָ����ĳ�ֲ���ʧȥƽ�����С�������ڵ�
AVLTree CAVLTree::SingleRightRotate(AVLTree T)
{
	AVLTree xPNode = T;
	AVLTree yPNode = T->left;
	xPNode->left = yPNode->right;//����ԭ���ڵ��������
	yPNode->right = xPNode;//����ԭ���ڵ����ӵ�������

	//���½�������ת�����Ľڵ�ĸ߶�
	xPNode->height = max(getHeight(xPNode->left),getHeight(xPNode->right)) + 1;
	yPNode->height = max(getHeight(yPNode->left),getHeight(yPNode->right)) + 1;

	//ԭ���ڵ�����ӽڵ��Ϊ�µĸ��ڵ�
	return yPNode;
}

//���������뵼�µĲ�ƽ�⣬���õ���ת-����ת��������
//�������ͣ�
//T��ָ����ĳ�ֲ���ʧȥƽ�����С�������ڵ�
AVLTree CAVLTree::SingleLeftRotate(AVLTree T)
{
	AVLTree xPNode = T;
	AVLTree yPNode = T->right;

	xPNode->right = yPNode->left;//����ԭ���ڵ���Һ���
	yPNode->left = xPNode;//����ԭ���ڵ���Һ��ӽڵ�Ϊ�µĸ��ڵ�

	//����ִ������ת�����Ľڵ�ĸ߶���Ϣ
	xPNode->height = max(getHeight(xPNode->left),getHeight(xPNode->right)) + 1;
	yPNode->height = max(getHeight(yPNode->left),getHeight(yPNode->right)) + 1;

	//�����µĸ��ڵ�
	return yPNode;
}

//�����λ��T�����ӽ���������
AVLTree CAVLTree::DoubleRightRotate(AVLTree T)
{
	//˫��ת����ͨ�����ε���תʵ��
	//��һ�ε���ת
	assert(T->left != NULL);
	//��������������һ�ε���ת-����ת
	T->left = SingleLeftRotate(T->left);
	//�ڶ��ε���ת
	//���²�����������һ�ε���ת-����ת
	return SingleRightRotate(T);
}

//�����λ��T�����ӽڵ��������
AVLTree CAVLTree::DoubleLeftRotate(AVLTree T)
{
	//˫��ת����ͨ�����ε���תʵ��
	//��һ�ε���ת
	assert(T->right != NULL);
	//��������������һ�ε���ת-����ת
	T->right = SingleRightRotate(T->right);
	//�ڶ��ε���ת
	//���²�����������һ�ε���ת-����ת
	return SingleLeftRotate(T);
}
