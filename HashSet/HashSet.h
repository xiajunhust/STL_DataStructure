//Hash Set ���ʵ�֣�SGI STL 5.8 Hash_set��
//Author���������꣨E-Mali��xiajunhust@gmail.com��

#include "HashTable.h"

//hash_set���ݽṹ����
template <class ValueType,
				class HashFcn = hash<ValueType>,
				class EqualKey = equal_to<ValueType> >
class HashSetClass{
private:
	//hash table���ͣ�������HashTable.h�У�
	//��ʱhash table�ļ�ֵ��ʵֵ���Ͷ���ValueType
	typedef HashTableClass<ValueType,ValueType,HashFcn,identity<ValueType>,EqualKey> ht;
	ht rep;

public:
	typedef typename HashTableClass<ValueType,ValueType,HashFcn,identity<ValueType>,EqualKey>::node HashNode;
	//Ĭ�Ϲ��캯����Ĭ��bucket sizeΪ100��
	HashSetClass():rep(100,HashFcn(),EqualKey()){}
	//һϵ�й��캯��
	explicit HashSetClass(size_t n):rep(n,HashFcn(),EqualKey()){}
	HashSetClass(size_t n,const HashFcn &hf):rep(n,hf,EqualKey()){}
	HashSetClass(size_t n,const HashFcn &hf,const EqualKey &eql):rep(n,hf,eql){}
	//��������
	~HashSetClass();

	size_t size(){return rep.size();}//set��Ԫ�ظ���
	size_t max_szie(){return rep.max_size();}//���Ԫ����Ŀ
	bool empty(){return rep.empty();}

	//����������������ظ�
	std::pair<HashNode*,bool> insert(const ValueType &obj)
	{
		std::pair<HashNode*,bool> result = rep.insert_unique(obj);
		if (false == result.second)
		{
			cout << "Warnnning : insert failed ! the same element " << obj << " has existed!" << endl;
		}
		return result;
	}

	//ɾ��Ԫ��
	size_t erase(const ValueType &obj){return rep.erase(obj);}

	void clear(){rep.clear();}

	HashNode* find(const ValueType &obj)
	{
		return (rep.find(obj)).first;
	}

	size_t count(const ValueType &obj) const {return rep.count(obj);}

	//���set������Ԫ��
	void printAllNodes();
};

template <class ValueType,class HashFcn,class EqualKey>
HashSetClass<ValueType,HashFcn,EqualKey>::~HashSetClass()
{

}

template <class ValueType,class HashFcn,class EqualKey>
void HashSetClass<ValueType,HashFcn,EqualKey>::printAllNodes()
{
	rep.printAllNodes();
}