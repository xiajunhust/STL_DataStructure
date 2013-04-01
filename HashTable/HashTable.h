//��STLԴ��������5.7 hashtable���ʵ��
//Author����������
//E-Mail��xiajunhust@gmail.com

#include <iostream>
#include <algorithm>
#include <vector>

//hash table������ڵ����ݽṹ����
template <class ValueType>
struct __hashtable_node{
	__hashtable_node *next;
	ValueType val;
};

static const int __stl_num_primes = 28;//����С(28������)
//28������
static const unsigned long __stl_prime_list[__stl_num_primes] = {
	53,         97,           193,         389,       769,
	1543,       3079,         6151,        12289,     24593,
	49157,      98317,        196613,      393241,    786433,
	1572869,    3145739,      6291469,     12582917,  25165843,
	50331653,   100663319,    201326611,   402653189, 805306457, 
	1610612741, 3221225473ul, 4294967291ul
};

//�ó�28�������в�С��n���Ǹ�����
inline unsigned long __get_next_prime(unsigned long n)
{
	const unsigned long *first = __stl_prime_list;
	const unsigned long *last = __stl_prime_list + __stl_num_primes;
	const unsigned long *pos = std::lower_bound(first,last,n);

	return pos == last ? *(last - 1) : *pos;
}

template <class T1,class T2>
void construct(T1 *p,const T2 &value)
{
	new (p) T1(value);
}

template <class T>
void destroy(T* pointer)
{
	pointer->~T();//������������
}

//hash��������
//���Ƿº���
template <class KeyType>
struct hash{};

//�ַ���Ҫ����ӳ��
inline size_t __stl_hash_string(const char *s)
{
	unsigned long h = 0;
	for (;*s;++s)
	{
		h = 5 * h + *s;
	}

	return size_t(h);
}

//��ģ����ʾ�ػ�����
template <>
struct hash<int>{
	size_t operator()(int x) const {return x;}
};

template <>
struct hash<char *>{
	size_t operator()(const char *s) const {return __stl_hash_string(s);}
};

template <>
struct hash<const char *>{
	size_t operator()(const char *s) const {return __stl_hash_string(s);}
};

template <>
struct hash<char>{
	size_t operator()(char s) const {return s;}
};

template <>
struct hash<unsigned char>{
	size_t operator()(unsigned char s) const {return s;}
};

template <>
struct hash<signed char>{
	size_t operator()(signed char s) const {return s;}
};

//hash table���ݽṹ����
//ģ�������
//ValueType���ڵ��ʵֵ�ͱ�
//KeyType���ڵ�ļ�ֵ�ͱ�
//HashFcn��hash function�ĺ����ͱ�
template <class ValueType,class KeyType,class HashFcn>
class HashTableClass{
public:
	typedef struct __hashtable_node<ValueType> node;//hash table�ڲ�����ڵ㶨��
	//hash tableû���ṩĬ�Ϲ��캯��
	HashTableClass(size_t n,const HashFcn &hf);
	~HashTableClass();
	//����Ԫ�ظ���
	size_t size(){return num_elements;}
	//����bucket vector��С
	size_t bucket_count(){return buckets.size();}
	//����bucket vector���ܵ����ֵ
	size_t max_bucket_count(){return __stl_prime_list[__stl_num_primes - 1];}
	//����Ԫ�أ��������ظ�
	std::pair<node *,bool> insert_unique(const ValueType &obj);
	//����Ԫ�أ������ظ�
	node* insert_equal(const ValueType &obj);
	//��ӡ���нڵ�
	void printAllNodes();
	//��������buckets
	void printAllBuckets();
	//����ĳһ��ֵ�Ľڵ�
	std::pair<node*,bool> find(const ValueType &obj);
	//�ж�ĳһֵ���ֵĴ���
	size_t count(const ValueType &obj);
	//����ɾ��
	void clear();
	//����hash��
	void copy_from(const HashTableClass *ht);

private:
	std::vector<node*> buckets;//��Ͱ��ɵ�vector
	size_t num_elements;//�ܵ�Ԫ�ظ���
	HashFcn hasher;

	//�ڵ����ú��ͷź���
	node* new_node(const ValueType &obj)
	{
		node *tempNode = new node;
		tempNode->next = NULL;
		try
		{
			construct(&tempNode->val,obj);
		}
		catch (...)
		{
			delete tempNode;
			throw;
			return NULL;
		}
		return tempNode;
	}

	void delete_node(node *n)
	{
		destroy(&n->val);
		delete n;
	}

	//��ʼ��buckets vector
	void initialize_buckets(size_t n);

	//������ӽ�n�����ڵ���n������
	size_t next_size(size_t n)const{return __get_next_prime(n);}

	//�ж��Ƿ���Ҫ����buckets vector��������Ҫ���������
	void resize(size_t num_elements_hint);

	//�ж�Ԫ�������ĸ�bucket
	//�����ṩ�����汾
	//�汾һ��ֻ���ܼ�ֵ
	size_t bkt_num_key(const KeyType &Key) const{return hasher(Key) % (buckets.size());}
	//�汾�������ܼ�ֵ��buckets����
	size_t bkt_num_key(const KeyType &Key,size_t n) const {return hasher(Key) % n;}

	//�ڲ���Ҫ���·���bucket vector������²���Ԫ�أ�Ԫ�ز������ظ�
	std::pair<node *,bool> insert_unique_noresize(const ValueType &obj);
	//�ڲ���Ҫ���·���bucket vector������²���Ԫ�أ�Ԫ�ز������ظ�
	node* insert_equal_noresize(const ValueType &obj);
};

template <class ValueType,class KeyType,class HashFcn>
HashTableClass<ValueType,KeyType,HashFcn>::HashTableClass(size_t n, const HashFcn &hf)
:hasher(hf),
num_elements(0)
{
	initialize_buckets(n);
}

template <class ValueType,class KeyType,class HashFcn>
HashTableClass<ValueType,KeyType,HashFcn>::~HashTableClass()
{
	clear();
};

template <class ValueType,class KeyType,class HashFcn>
std::pair<typename HashTableClass<ValueType,KeyType,HashFcn>::node *,bool> 
HashTableClass<ValueType,KeyType,HashFcn>::insert_unique(const ValueType &obj)
{
	resize(num_elements + 1);

	return insert_unique_noresize(obj);
}

template <class ValueType,class KeyType,class HashFcn>
typename HashTableClass<ValueType,KeyType,HashFcn>::node *
HashTableClass<ValueType,KeyType,HashFcn>::insert_equal(const ValueType &obj)
{
	resize(num_elements + 1);

	return insert_equal_noresize(obj);
}

template <class ValueType,class KeyType,class HashFcn>
void HashTableClass<ValueType,KeyType,HashFcn>::printAllNodes()
{
	cout << endl;
	cout << "Current node in hash table : " << endl;
	for (size_t i = 0;i < buckets.size();++i)
	{
		typename HashTableClass<ValueType,KeyType,HashFcn>::node* curNode = buckets[i];
		while(curNode)
		{
			cout << curNode->val << " ";
			curNode = curNode->next;
		}
	}
	cout << endl;
}

template <class ValueType,class KeyType,class HashFcn>
void HashTableClass<ValueType,KeyType,HashFcn>::printAllBuckets()
{
	cout << endl;
	cout << "Current buckets in hash table : " << endl;
	for (size_t i = 0;i < buckets.size();++i)
	{
		typename HashTableClass<ValueType,KeyType,HashFcn>::node* curNode = buckets[i];
		if(NULL == curNode)
			cout << "buckets[" << i << "] is empty!" << endl;
		else
		{
			size_t count = 0;
			while(curNode)
			{
				++count;
				curNode = curNode->next;
			}
			cout << "buckets[" << i << "] has " << count << " elements : ";
			curNode = buckets[i];
			while(curNode)
			{
				cout << curNode->val << " ";
				curNode = curNode->next;
			}
			cout << endl;
		}
	}
}

template <class ValueType,class KeyType,class HashFcn>
std::pair<typename HashTableClass<ValueType,KeyType,HashFcn>::node *,bool> 
HashTableClass<ValueType,KeyType,HashFcn>::find(const ValueType &obj)
{
	size_t bucket_index = bkt_num_key(obj);
	node*first = buckets[bucket_index];
	while(first)
	{
		if (obj == first->val)
		{
			cout << "find the element " << obj << " success" << endl;
			return std::pair<typename HashTableClass<ValueType,KeyType,HashFcn>::node *,bool>(first,true);
		}
		first = first->next;
	}

	cout << "cannot find the element " << obj << endl;

	return std::pair<typename HashTableClass<ValueType,KeyType,HashFcn>::node *,bool>(NULL,false);
}

template <class ValueType,class KeyType,class HashFcn>
size_t HashTableClass<ValueType,KeyType,HashFcn>::count(const ValueType &obj)
{
	size_t bucket_index = bkt_num_key(obj);
	node*first = buckets[bucket_index];
	size_t num = 0;
	while(first)
	{
		if (obj == first->val)
		{
			++num;
		}
		first = first->next;
	}

	cout << "The element " << obj << " appears " << num << " times" << endl;
	return num;
}

template <class ValueType,class KeyType,class HashFcn>
void HashTableClass<ValueType,KeyType,HashFcn>::clear()
{
	for (size_t i = 0;i < buckets.size();++i)
	{
		node* first = buckets[i];
		//ɾ��bucket list�е�ÿ���ڵ�
		while(first)
		{
			node *next = first->next;
			delete_node(first);
			first = next;
		}
		buckets[i] = 0;
	}
	//��Ԫ�ظ�����0
	num_elements = 0;

	//vector��δ�ͷŵ��ռ䣨�Զ����գ�
}

template <class ValueType,class KeyType,class HashFcn>
void HashTableClass<ValueType,KeyType,HashFcn>::copy_from(const HashTableClass *ht)
{
	buckets.clear();//�������vector
	//ʹ��bucket vector�ռ�ͶԷ���ͬ
	buckets.reserve(ht->buckets.size());
	//����n��Ԫ�أ�null
	buckets.insert(buckets.end(),ht->buckets.size(),(typename HashTableClass<ValueType,KeyType,HashFcn>::node *)0);

	for (size_t i = 0;i < ht->buckets.size();++i)
	{
		if (const node *cur = ht->buckets[i])
		{
			node *tempNode = new_node(cur->val);
			buckets[i] = tempNode;
			for (node *next = cur->next;next;next = next->next)
			{
				tempNode->next = new_node(next->val);
				tempNode = tempNode->next;
			}
		}
	}

	num_elements = ht->num_elements;
}

template <class ValueType,class KeyType,class HashFcn>
void HashTableClass<ValueType,KeyType,HashFcn>::initialize_buckets(size_t n)
{
	const size_t n_buckets = next_size(n);
	buckets.reserve(n_buckets);
	buckets.insert(buckets.end(),n_buckets,(node*)0);
}

template <class ValueType,class KeyType,class HashFcn>
void HashTableClass<ValueType,KeyType,HashFcn>::resize(size_t num_elements_hint)
{
	//buckets vector�ؽ����ı�׼��
	//�Ƚ��µ���Ԫ�ظ�����ԭbuckets vector��С
	const size_t old_n_vector = buckets.size();
	//��Ҫ��������
	if (num_elements_hint > old_n_vector)
	{
		const size_t n = next_size(num_elements_hint);
		vector<node*> tempVec(n,(node *)0);
		for (size_t bucketIndex = 0;bucketIndex < old_n_vector;++bucketIndex)
		{
			node *first = buckets[bucketIndex];//ָ��ڵ��Ӧ֮���е���ʼ�ڵ�
			while(first)
			{
				//����ڵ�������һ���µ�bucket��
				size_t new_bucket_index = bkt_num_key(first->val,n);
				buckets[bucketIndex] = first->next;
				first->next = tempVec[new_bucket_index];
				tempVec[new_bucket_index] = first;
				first = buckets[bucketIndex];
			}
		}
		//�����¾�����bucket vector
		buckets.swap(tempVec);
	}
}

template <class ValueType,class KeyType,class HashFcn>
std::pair<typename HashTableClass<ValueType,KeyType,HashFcn>::node *,bool> 
HashTableClass<ValueType,KeyType,HashFcn>::insert_unique_noresize(const ValueType &obj)
{
	size_t bucket_index = bkt_num_key(obj);
	node *first = buckets[bucket_index];
	//������ǰ����
	for (node *curNode = first;curNode;curNode = curNode->next)
	{
		if(obj == curNode->val)
			return pair<typename HashTableClass<ValueType,KeyType,HashFcn>::node*,bool>(curNode,false);
	}

	node *tempNode = new_node(obj);
	tempNode->next = first;
	buckets[bucket_index] = tempNode;

	++num_elements;

	return pair<typename HashTableClass<ValueType,KeyType,HashFcn>::node*,bool>(tempNode,true);
}

template <class ValueType,class KeyType,class HashFcn>
typename HashTableClass<ValueType,KeyType,HashFcn>::node*
HashTableClass<ValueType,KeyType,HashFcn>::insert_equal_noresize(const ValueType &obj)
{
	size_t bucket_index = bkt_num_key(obj);
	node *first = buckets[bucket_index];
	for (node *curNode = first;curNode;curNode = curNode->next)
	{
		//�����������е�ĳ��ֵ��ȣ����ϲ��룬Ȼ�󷵻�
		if (obj == curNode->val)
		{
			node *tempNode = new_node(obj);
			tempNode->next = curNode->next;
			curNode->next = tempNode;
			++num_elements;
			return tempNode;
		}
	}

	//���û���ּ�ֵ��ȵ�Ԫ��
	node *tempNode = new_node(obj);
	//�����������ͷ��
	tempNode->next = first;
	buckets[bucket_index] = tempNode;
	++num_elements;
	return tempNode;
}