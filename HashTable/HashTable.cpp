#include "HashTable.h"

using namespace std;

int main()
{
	HashTableClass<int,int,hash<int> > *hashTableObj = new HashTableClass<int,int,hash<int> >(50,hash<int>());

	cout << "Hash Table size : " << hashTableObj->size() << endl;
	cout << "Hash Table bucket count : " << hashTableObj->bucket_count() << endl;
	cout << "Hash Table max bucket count : " << hashTableObj->max_bucket_count() << endl;

	hashTableObj->insert_unique(59);
	hashTableObj->insert_unique(63);
	hashTableObj->insert_unique(108);
	hashTableObj->insert_unique(2);
	hashTableObj->insert_unique(53);
	hashTableObj->insert_unique(55);
	cout << "Hash Table size : " << hashTableObj->size() << endl;
	hashTableObj->printAllNodes();
	hashTableObj->printAllBuckets();

	//继续插入元素，使总元素个数达到54个
	for(int i = 0;i <= 47;++i)
		hashTableObj->insert_equal(i);
	cout << endl;
	cout << "Hash Table size : " << hashTableObj->size() << endl;
	cout << "Hash Table bucket count : " << hashTableObj->bucket_count() << endl;
	hashTableObj->printAllNodes();
	hashTableObj->printAllBuckets();

	hashTableObj->find(2);
	hashTableObj->count(2);

	HashTableClass<int,int,hash<int> > *hashTableObj2 = new HashTableClass<int,int,hash<int> >(20,hash<int>());

	cout << "Hash Table 2 size : " << hashTableObj2->size() << endl;
	cout << "Hash Table 2 bucket count : " << hashTableObj2->bucket_count() << endl;
	cout << "Hash Table 2 max bucket count : " << hashTableObj2->max_bucket_count() << endl;

	hashTableObj2->copy_from(hashTableObj);
	cout << "Hash Table 2 size : " << hashTableObj2->size() << endl;
	cout << "Hash Table 2 bucket count : " << hashTableObj2->bucket_count() << endl;
	cout << "Hash Table 2 max bucket count : " << hashTableObj2->max_bucket_count() << endl;

	delete hashTableObj;
	delete hashTableObj2;

	return 0;
}