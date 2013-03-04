#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

//AVL�����ݽṹ����
typedef int ElementType;//AVL���ڵ������������

//���ڵ�
typedef struct AVLNode{
	ElementType element;//�ڵ����������Ԫ��
	AVLNode *left;//�ڵ�������
	AVLNode *right;//�ڵ�������
	int height;//�ڵ����ڵĸ߶�
}*AVLTree;

//AVL tree���װ
class CAVLTree{
private:
	//���ڲ����õĺ���
	int getHeight(AVLTree);//������ĸ߶�

	void setHeight(AVLTree,int);//���ýڵ�ĸ߶�ֵ

	//����ת��������ת
	AVLTree SingleRightRotate(AVLTree);
	//����ת��������ת
	AVLTree SingleLeftRotate(AVLTree);
	//˫��ת������
	AVLTree DoubleRightRotate(AVLTree);
	//˫��ת������
	AVLTree DoubleLeftRotate(AVLTree);

public:
	//Ĭ�Ϲ��캯��
	CAVLTree();
	//��������
	~CAVLTree();
	//����AVL��
	void createAVLTree(ElementType *data,int n);
	//����ڵ�
	AVLTree insertNode(AVLTree T,ElementType val);
	//ɾ������Ԫ��ֵ����ĳֵ�Ľڵ�
	AVLTree deleteNode(AVLTree T,const ElementType val);
	//��ѰԪ��ֵ����ĳֵ�Ľڵ�
	AVLTree searchNode(AVLTree,ElementType);
	//ǰ����������
	void preOrder(AVLTree T);
	//�õ����е�Ԫ��ֵ���Ľڵ�
	AVLTree getMaxNode(AVLTree);
	//�õ����е�Ԫ��ֵ��С���Ǹ��ڵ�
	AVLTree getMinNode(AVLTree);

	AVLTree T;
};

#endif // AVLTREE_H_INCLUDED
