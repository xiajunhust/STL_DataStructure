#include "HashSet.h"

using namespace std;

int main()
{
	HashSetClass<const char *,hash<const char *>,eqstr> *hashSetObj = new HashSetClass<const char *,hash<const char *>,eqstr>;

	hashSetObj->insert("kiwi");
	hashSetObj->insert("plum");
	hashSetObj->insert("apple");
	hashSetObj->insert("mango");
	hashSetObj->insert("apricot");
	hashSetObj->insert("banana");
	cout << "Current node in hash set : " << endl;
	hashSetObj->printAllNodes();

	hashSetObj->find("mango");
	hashSetObj->find("HUST");

	hashSetObj->insert("banana");

	char *erased_string = "jun";
	size_t erased_nodes = hashSetObj->erase(erased_string);
	if (!erased_nodes)
	{
		cout << "Warnning : erase failed ! Cannot find the node equals " << erased_string << " in the hash table" << endl;
	}
	else{
		cout << "erase " << erased_nodes << " nodes equal the " << erased_string << " in the hash table" << endl;
		cout << "After erased : " << endl;
		hashSetObj->printAllNodes();
	}

	erased_string = "banana";
	erased_nodes = hashSetObj->erase(erased_string);
	if (!erased_nodes)
	{
		cout << "Warnning : erase failed ! Cannot find the node equals " << erased_string << " in the hash table" << endl;
	}
	else{
		cout << "erase " << erased_nodes << " nodes equal the " << erased_string << " in the hash table" << endl;
		cout << "After erased : " << endl;
		hashSetObj->printAllNodes();
	}

	HashSetClass<int> *hashSetObj2 = new HashSetClass<int>;
	hashSetObj2->insert(3);
	hashSetObj2->insert(196);
	hashSetObj2->insert(1);
	hashSetObj2->insert(389);
	hashSetObj2->insert(194);
	hashSetObj2->insert(387);

	hashSetObj2->printAllNodes();

	delete hashSetObj;

	return 0;
}