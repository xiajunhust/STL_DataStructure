//��STLԴ��������5.7 hashtable���ʵ��
//Author����������
//E-Mail��xiajunhust@gmail.com

#include <iostream>
#include <algorithm>
#include <vector>

//hash table�������ڵ����ݽṹ����
template <class ValueType>
struct __hashtable_node{
	__hashtable_node *next;
	ValueType val;
};

static const int __stl_num_primes = 28;//�����С(28������)
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

// C++ Standard �涨��ÿһ�� Adaptable Unary Function ������̳д����
template <class Arg,class Result>
struct unary_function{
	typedef Arg argument_type;
	typedef Result result_type;
};

// C++ Standard �涨��ÿһ�� Adaptable Binary Function ������̳д����
template <class Arg1,class Arg2,class Result>
struct binary_function{
	typedef Arg1 first_argument_type;
	typedef Arg2 second_argument_type;
	typedef Result result_type;
};

//�ӽڵ���ȡ����ֵ�ķº�������
//identity function���κ���ֵͨ���˺���ʽ�󣬲��ᷢ���κθı�
template <class T>
struct identity:public unary_function<T,T>
{
	const T& operator()(const T& x) const{return x;}
};

//�жϼ�ֵ�Ƿ���ȵķº�������
template <class T>
struct equal_to:public binary_function<T,T,bool>{
	bool operator()(const T& x,const T& y) const{return x == y;}
};

//�Ƚ��ַ����Ƿ���ȵķº���
struct eqstr{
	bool operator()(const char *s1,const char *s2)const
	{
		return strcmp(s1,s2) == 0;
	}
};

//hash table���ݽṹ����
//ģ�������
//ValueType���ڵ��ʵֵ�ͱ�
//KeyType���ڵ�ļ�ֵ�ͱ�
//HashFcn��hash function�ĺ����ͱ�
//ExtractKey���ӽڵ���ȡ����ֵ�ķ���
//EqualKey���жϼ�ֵ�Ƿ���ͬ
template <class ValueType,class KeyType,class HashFcn,class ExtractKey,class EqualKey>
class HashTableClass{
public:
	typedef struct __hashtable_node<ValueType> node;//hash table�ڲ������ڵ㶨��
	//hash tableû���ṩĬ�Ϲ��캯��
	HashTableClass(size_t n,
		const HashFcn &hf,
		const EqualKey &eql,
		const ExtractKey &ext)
		:hasher(hf),equals(eql),get_key(ext),num_elements(0)
	{
		initialize_buckets(n);
	}
	HashTableClass(size_t n,
		const HashFcn &hf,
		const EqualKey &eql)
		:hasher(hf),equals(eql),get_key(ExtractKey()),num_elements(0)
	{
		initialize_buckets(n);
	}
	HashTableClass(const HashTableClass &ht)
		:hasher(ht.hasher),equals(ht.equals),get_key(ht.get_key),num_elements(0)
	{
		copy_from(&ht);
	}
	~HashTableClass(){clear();};
	//��ֵ������
	HashTableClass& operator= (const HashTableClass &ht)
	{
		if (&ht != this)
		{
			clear();
			hasher = ht.hasher;
			equals = ht.equals;
			get_key = ht.get_key;
			copy_from(&ht);
		}
	}
	//����Ԫ�ظ���
	size_t size(){return num_elements;}
	//���Ԫ����Ŀ
	size_t max_size(){return size_t(-1);}
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
	std::pair<node*,bool> find(const KeyType &key);
	//�ж�ĳһֵ���ֵĴ���
	size_t count(const KeyType &key);
	//ɾ������ĳһ��ֵ�����нڵ�
	size_t erase(const KeyType &key);
	//����ɾ��
	void clear();
	//����hash��
	void copy_from(const HashTableClass *ht);

private:
	std::vector<node*> buckets;//��Ͱ��ɵ�vector
	size_t num_elements;//�ܵ�Ԫ�ظ���
	HashFcn hasher;
	ExtractKey get_key;
	EqualKey equals;

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
	//�ṩ�����汾
	//�汾һ��ֻ����ʵֵ
	size_t bkt_num(const ValueType &obj) const{return bkt_num_key(get_key(obj));}
	//�汾��������ʵֵ��buckets����
	size_t bkt_num(const ValueType &obj,size_t n) const {return bkt_num_key(get_key(obj),n);}
	//�汾һ��ֻ���ܼ�ֵ
	size_t bkt_num_key(const KeyType &Key) const{return hasher(Key) % (buckets.size());}
	//�汾�������ܼ�ֵ��buckets����
	size_t bkt_num_key(const KeyType &Key,size_t n) const {return hasher(Key) % n;}

	//�ڲ���Ҫ���·���bucket vector������²���Ԫ�أ�Ԫ�ز������ظ�
	std::pair<node *,bool> insert_unique_noresize(const ValueType &obj);
	//�ڲ���Ҫ���·���bucket vector������²���Ԫ�أ�Ԫ�ز������ظ�
	node* insert_equal_noresize(const ValueType &obj);
};

template <class ValueType,class KeyType,class HashFcn,class ExtractKey,class EqualKey>
std::pair<typename HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::node *,bool> 
HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::insert_unique(const ValueType &obj)
{
	resize(num_elements + 1);

	return insert_unique_noresize(obj);
}

template <class ValueType,class KeyType,class HashFcn,class ExtractKey,class EqualKey>
typename HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::node *
HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::insert_equal(const ValueType &obj)
{
	resize(num_elements + 1);

	return insert_equal_noresize(obj);
}

template <class ValueType,class KeyType,class HashFcn,class ExtractKey,class EqualKey>
void HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::printAllNodes()
{
	cout << "Current node in hash table : " << endl;
	for (size_t i = 0;i < buckets.size();++i)
	{
		typename HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::node* curNode = buckets[i];
		while(curNode)
		{
			cout << curNode->val << " ";
			curNode = curNode->next;
		}
	}
	cout << endl;
}

template <class ValueType,class KeyType,class HashFcn,class ExtractKey,class EqualKey>
void HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::printAllBuckets()
{
	cout << "Current buckets in hash table : " << endl;
	for (size_t i = 0;i < buckets.size();++i)
	{
		typename HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::node* curNode = buckets[i];
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

template <class ValueType,class KeyType,class HashFcn,class ExtractKey,class EqualKey>
std::pair<typename HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::node *,bool> 
HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::find(const KeyType &key)
{
	size_t bucket_index = bkt_num_key(key);
	node*first = buckets[bucket_index];
	while(first)
	{
		if (equals(key,get_key(first->val)))
		{
			cout << "find the element " << key << " success" << endl;
			return std::pair<typename HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::node *,bool>(first,true);
		}
		first = first->next;
	}

	cout << "cannot find the element " << key << endl;

	return std::pair<typename HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::node *,bool>(NULL,false);
}

template <class ValueType,class KeyType,class HashFcn,class ExtractKey,class EqualKey>
size_t HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::count(const KeyType &key)
{
	size_t bucket_index = bkt_num_key(key);
	node*first = buckets[bucket_index];
	size_t num = 0;
	while(first)
	{
		if (equals(key,get_key(first->val)))
		{
			++num;
		}
		first = first->next;
	}

	cout << "The element " << key << " appears " << num << " times" << endl;
	return num;
}

template <class ValueType,class KeyType,class HashFcn,class ExtractKey,class EqualKey>
size_t HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::erase(const KeyType &key)
{
	size_t erased_nodes = 0;//��¼��ɾ������Ԫ����
	size_t bucket_index = bkt_num_key(key);
	node *first = buckets[bucket_index];
	if (first)
	{
		node *cur = first,*next = first->next;
		//�������еڶ����ڵ㿪ʼ�ж�
		while(next)
		{
			//�ҵ���ֵ��ȵ�Ԫ�أ�ɾ��
			if (equals(next->val,key))
			{
				cur->next = next->next;
				delete_node(next);
				next = cur->next;
				++erased_nodes;
				--num_elements;
			}
			else{
				cur = next;
				next = next->next;
			}
		}

		//���жϵ�һ���ڵ�
		if (equals(first->val,key))
		{
			buckets[bucket_index] = first->next;
			delete_node(first);
			++erased_nodes;
			--num_elements;
		}
	}

	return erased_nodes;
}

template <class ValueType,class KeyType,class HashFcn,class ExtractKey,class EqualKey>
void HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::clear()
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

template <class ValueType,class KeyType,class HashFcn,class ExtractKey,class EqualKey>
void HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::copy_from(const HashTableClass *ht)
{
	buckets.clear();//�������vector
	//ʹ��bucket vector�ռ�ͶԷ���ͬ
	buckets.reserve(ht->buckets.size());
	//����n��Ԫ�أ�null
	buckets.insert(buckets.end(),ht->buckets.size(),(typename HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::node *)0);

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

template <class ValueType,class KeyType,class HashFcn,class ExtractKey,class EqualKey>
void HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::initialize_buckets(size_t n)
{
	const size_t n_buckets = next_size(n);
	buckets.reserve(n_buckets);
	buckets.insert(buckets.end(),n_buckets,(node*)0);
}

template <class ValueType,class KeyType,class HashFcn,class ExtractKey,class EqualKey>
void HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::resize(size_t num_elements_hint)
{
	//buckets vector�ؽ����ı�׼��
	//�Ƚ��µ���Ԫ�ظ�����ԭbuckets vector��С
	const size_t old_n_vector = buckets.size();
	//��Ҫ��������
	if (num_elements_hint > old_n_vector)
	{
		const size_t n = next_size(num_elements_hint);
		if (n > old_n_vector)//�п���vector�ѵ������
		{
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
}

template <class ValueType,class KeyType,class HashFcn,class ExtractKey,class EqualKey>
std::pair<typename HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::node *,bool> 
HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::insert_unique_noresize(const ValueType &obj)
{
	size_t bucket_index = bkt_num(obj);
	node *first = buckets[bucket_index];
	//������ǰ����
	for (node *curNode = first;curNode;curNode = curNode->next)
	{
		if(equals(get_key(obj),get_key(curNode->val)))
			return pair<typename HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::node*,bool>(curNode,false);
	}

	node *tempNode = new_node(obj);
	tempNode->next = first;
	buckets[bucket_index] = tempNode;

	++num_elements;

	return pair<typename HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::node*,bool>(tempNode,true);
}

template <class ValueType,class KeyType,class HashFcn,class ExtractKey,class EqualKey>
typename HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::node*
HashTableClass<ValueType,KeyType,HashFcn,ExtractKey,EqualKey>::insert_equal_noresize(const ValueType &obj)
{
	size_t bucket_index = bkt_num(obj);
	node *first = buckets[bucket_index];
	for (node *curNode = first;curNode;curNode = curNode->next)
	{
		//�����������е�ĳ��ֵ��ȣ����ϲ��룬Ȼ�󷵻�
		if (equals(get_key(obj),get_key(curNode->val)))
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