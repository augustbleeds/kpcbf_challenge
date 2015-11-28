#include "MyHashMap.h"
#include <iostream>
using namespace std;

int main(void){

	cout << "Create a map of size 5" << endl;

	myHashMap map(5);

	char key1[] = "tasdflk;j";
	int x = 3;
	map.set(key1, &x );

	cout << "After entering 1 key/value: load factor = " <<  map.load()  << endl;

	char key2[] = "thisiskey2";
	char y = 'a';
	map.set(key2, &y);

	cout << "After entering 2 key/value: load factor = " <<  map.load()  << endl;

	char key3[] = "aaaaaaaaa";
	float z = 777.777;
	map.set(key3, &z);

	cout << "After entering 3 key/value: load factor = " <<  map.load()  << endl;

	char key4[] = "abc";
	float pi = 3.14;
	map.set(key4, &pi );

	cout << "After entering 4 key/value: load factor = " <<  map.load()  << endl;

	char key5[] = "asdfasdf";
	bool isTrue = false;
	map.set(key5, &isTrue);

	cout << "After entering 5 key/value: load factor = " <<  map.load()  << endl;

	char key6[] = "xyz";
	int num = 2;
	cout << "Attempting to add key/value entry to exceed the capacity of the hashmap" << endl;
	map.set(key6, &num);

	cout << "Get a value associated with key3 " << endl;
	cout << "Result of get() is " << *(float *)map.get(key3) << " and value should be " << z << endl;

	cout << "Delete key4 entry" << endl;
	cout << "Delete has resulted in delete() returning " << *(float *)map.deleteit(key4) << ". Load factor is now " << map.load() << endl;

	cout << "EXIT PROGRAM. . ." << endl;


}