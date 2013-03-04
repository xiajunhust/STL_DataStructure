#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

//AVL树数据结构定义
typedef int ElementType;//AVL数节点包含数据类型

//树节点
typedef struct AVLNode{
	ElementType element;//节点包含的数据元素
	AVLNode *left;//节点左子树
	AVLNode *right;//节点右子树
	int height;//节点所在的高度
}*AVLTree;

//AVL tree类封装
class CAVLTree{
private:
	//供内部调用的函数
	int getHeight(AVLTree);//求得树的高度

	void setHeight(AVLTree,int);//设置节点的高度值

	//单旋转：向右旋转
	AVLTree SingleRightRotate(AVLTree);
	//单旋转：向左旋转
	AVLTree SingleLeftRotate(AVLTree);
	//双旋转：左右
	AVLTree DoubleRightRotate(AVLTree);
	//双旋转：右左
	AVLTree DoubleLeftRotate(AVLTree);

public:
	//默认构造函数
	CAVLTree();
	//析构函数
	~CAVLTree();
	//创建AVL树
	void createAVLTree(ElementType *data,int n);
	//插入节点
	AVLTree insertNode(AVLTree T,ElementType val);
	//删除树中元素值等于某值的节点
	AVLTree deleteNode(AVLTree T,const ElementType val);
	//搜寻元素值等于某值的节点
	AVLTree searchNode(AVLTree,ElementType);
	//前序遍历输出树
	void preOrder(AVLTree T);
	//得到树中的元素值最大的节点
	AVLTree getMaxNode(AVLTree);
	//得到树中的元素值最小的那个节点
	AVLTree getMinNode(AVLTree);

	AVLTree T;
};

#endif // AVLTREE_H_INCLUDED
