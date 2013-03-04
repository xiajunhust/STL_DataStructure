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

//依据各元素的数据值，创建AVL树
void CAVLTree::createAVLTree(ElementType *data,int n)
{
	if (T)
	{
		cout << "The AVL Tree has been created" << endl;

		return;
	}

	if(!n)//元素序列为空
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
	pNewNode->height = 1;//新节点一定被插入在空节点的位置

	if(NULL == T)
	{
		T = pNewNode;
		return T;
	}

	//需要插入节点的树非空
	//插入的元素已经存在于树中，不符合要求
	if (val == T->element)
	{
		cout << "元素中有重复，构建AVL树失败！" << endl;
		return T;
	}
	//要插入的值小于根节点的值，将其插入左子树中
	if(val < T->element)
	{
		//将其插入根节点的左子树中
		T->left = insertNode(T->left,val);
		//判断平衡条件是否仍然满足
		if(getHeight(T->left) - getHeight(T->right) > 1)
		{
			//分两种情况进行旋转操作
			//插入点位于T的左子结点的左子树
			if(val < T->left->element)
				//实施单旋转-右旋转
				T = SingleRightRotate(T);
			else
				//插入点位于T的左子结点的右子树，实施双右旋转
				T = DoubleRightRotate(T);
		}
	}
	//要插入的值大于根节点的值，将其插入右子树中
	if(val > T->element)
	{
		T->right = insertNode(T->right,val);
		//判断平衡条件是否仍然满足
		if(getHeight(T->right) - getHeight(T->left) > 1)
		{
			//节点插入到T的右子节点的右子树中
			if(val > T->right->element)
				//实施单旋转-左旋转
				T = SingleLeftRotate(T->right);
			else
				//节点插入到T的右子节点的左子树上
				//实施双旋转-左旋转
				T = DoubleLeftRotate(T);
		}
	}

	//更新节点的height值
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
	//没有找到相应的节点，删除失败
	if (!searchedNode)
	{
		cout << "Cann't find the node whose element equals " << val << endl;
		return T;
	} 
	
	//找到了需要删除的节点
	//需要删除的节点就是当前子树的根节点
	if (val == T->element)
	{
		//左右子树都非空
		if (T->left && T->right)
		{
			//在高度更大的那个子树上进行删除操作
			if (getHeight(T->left) > getHeight(T->right))
			{
				//左子树高度大，删除左子树中元素值最大的那个节点
				T->element = getMaxNode(T->left)->element;
				T->left = deleteNode(T->left,T->element);
			}
			else{
				//删除右子树中元素值最小的那个节点
				T->element = getMinNode(T->right)->element;
				T->right = deleteNode(T->right,T->element);
			}
		}
		else{
			//左右子树中有一个不为空，那个直接用需要被删除的节点的子节点替换之即可
			AVLTree oldNode = T;
			T = (T->left ? T->left : T->right);
			delete oldNode;//释放节点所占的空间
		}
	}
	else if (val < T->element)//要删除的节点在左子树中
	{
		//在左子树中进行删除
		T->left = deleteNode(T->left,val);
		//判断是否仍然满足平衡条件
		if (getHeight(T->right) - getHeight(T->left) > 1)
		{
			if (T->right->left > T->right->right)
			{
				//左双旋转
				T = DoubleLeftRotate(T);
			}
			else//进行左单旋转
				T = SingleLeftRotate(T);
		}
		else
			//满足平衡条件，需要更新高度信息
			T->height = max(getHeight(T->left),getHeight(T->right)) + 1;
	}
	else//需要删除的节点在右子树中
	{
		T->right = deleteNode(T->right,val);
		//判断是否满足平衡条件
		if (getHeight(T->left) - getHeight(T->right) > 1)
		{
			if(getHeight(T->left->right) > getHeight(T->left->left))
				//右双旋转
				T = DoubleRightRotate(T);
			else
				//右单旋转
				T = SingleRightRotate(T);
		}
		else
			//只需调整高度即可
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

	//搜索到
	if (val == T->element)
	{
		return T;
	}
	else if (val < T->element)
	{
		//在左子树中搜索
		return searchNode(T->left,val);
	}
	else
	{
		//在右子树中搜索
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
	if (!T)//树为空
	{
		return NULL;
	}

	AVLTree tempNode = T;
	//向右搜寻直至右子节点为NULL
	while(tempNode->right)
	{
		tempNode = tempNode->right;
	}

	return tempNode;
}

AVLTree CAVLTree::getMinNode(AVLTree T)
{
	if (!T)//树为空
	{
		return NULL;
	}

	AVLTree tempNode = T;
	//向左搜寻直至左子结点为NULL
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

//左左外侧插入导致的不平衡，采用单旋转-右旋转进行修正
//参数解释：
//T：指向因某种操作失去平衡的最小子树根节点
AVLTree CAVLTree::SingleRightRotate(AVLTree T)
{
	AVLTree xPNode = T;
	AVLTree yPNode = T->left;
	xPNode->left = yPNode->right;//更改原根节点的左子树
	yPNode->right = xPNode;//更改原根节点左孩子的右子树

	//更新进行了旋转操作的节点的高度
	xPNode->height = max(getHeight(xPNode->left),getHeight(xPNode->right)) + 1;
	yPNode->height = max(getHeight(yPNode->left),getHeight(yPNode->right)) + 1;

	//原根节点的左孩子节点成为新的根节点
	return yPNode;
}

//右右外侧插入导致的不平衡，采用单旋转-左旋转进行修正
//参数解释：
//T：指向因某种操作失去平衡的最小子树根节点
AVLTree CAVLTree::SingleLeftRotate(AVLTree T)
{
	AVLTree xPNode = T;
	AVLTree yPNode = T->right;

	xPNode->right = yPNode->left;//更改原根节点的右孩子
	yPNode->left = xPNode;//提升原根节点的右孩子节点为新的根节点

	//更新执行了旋转操作的节点的高度信息
	xPNode->height = max(getHeight(xPNode->left),getHeight(xPNode->right)) + 1;
	yPNode->height = max(getHeight(yPNode->left),getHeight(yPNode->right)) + 1;

	//返回新的根节点
	return yPNode;
}

//插入点位于T的左子结点的右子树
AVLTree CAVLTree::DoubleRightRotate(AVLTree T)
{
	//双旋转可以通过两次单旋转实现
	//第一次单旋转
	assert(T->left != NULL);
	//对其左子树进行一次单旋转-左旋转
	T->left = SingleLeftRotate(T->left);
	//第二次单旋转
	//对新产生的树进行一次单旋转-右旋转
	return SingleRightRotate(T);
}

//插入点位于T的右子节点的左子树
AVLTree CAVLTree::DoubleLeftRotate(AVLTree T)
{
	//双旋转可以通过两次单旋转实现
	//第一次单旋转
	assert(T->right != NULL);
	//对其右子树进行一次单旋转-右旋转
	T->right = SingleRightRotate(T->right);
	//第二次单旋转
	//对新产生的树进行一次单旋转-左旋转
	return SingleLeftRotate(T);
}
