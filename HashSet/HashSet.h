//Hash Set 编程实现（SGI STL 5.8 Hash_set）
//Author：江南烟雨（E-Mali：xiajunhust@gmail.com）

#include "HashTable.h"

//hash_set数据结构定义
template <class ValueType,
				class HashFcn = hash<ValueType>,
				class EqualKey = equal_to<ValueType> >
class HashSetClass{
private:
	//hash table类型（定义于HashTable.h中）
	//此时hash table的键值和实值类型都是ValueType
	typedef HashTableClass<ValueType,ValueType,HashFcn,identity<ValueType>,EqualKey> ht;
	ht rep;

public:
	typedef typename HashTableClass<ValueType,ValueType,HashFcn,identity<ValueType>,EqualKey>::node HashNode;
	//默认构造函数（默认bucket size为100）
	HashSetClass():rep(100,HashFcn(),EqualKey()){}
	//一系列构造函数
	explicit HashSetClass(size_t n):rep(n,HashFcn(),EqualKey()){}
	HashSetClass(size_t n,const HashFcn &hf):rep(n,hf,EqualKey()){}
	HashSetClass(size_t n,const HashFcn &hf,const EqualKey &eql):rep(n,hf,eql){}
	//析构函数
	~HashSetClass();

	size_t size(){return rep.size();}//set中元素个数
	size_t max_szie(){return rep.max_size();}//最大元素数目
	bool empty(){return rep.empty();}

	//插入操作，不允许重复
	std::pair<HashNode*,bool> insert(const ValueType &obj)
	{
		std::pair<HashNode*,bool> result = rep.insert_unique(obj);
		if (false == result.second)
		{
			cout << "Warnnning : insert failed ! the same element " << obj << " has existed!" << endl;
		}
		return result;
	}

	//删除元素
	size_t erase(const ValueType &obj){return rep.erase(obj);}

	void clear(){rep.clear();}

	HashNode* find(const ValueType &obj)
	{
		return (rep.find(obj)).first;
	}

	size_t count(const ValueType &obj) const {return rep.count(obj);}

	//输出set中所有元素
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