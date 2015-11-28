#include "myHashMap.h"
#include <iostream>

using namespace std;

/*
 * Class Constructor.
 * 
 * Input: The size of the hashMap.
 *
 * a. Initializes size and count.
 * b. Creates a dynamically allocated map of a certain size.
 * c. Initialize each Bucket's front Node pointer to NULL.
 */

myHashMap::myHashMap(uint32_t size)
: size(size), count(0)						// (a) member initialization 
{				
	this->map = new Bucket[size];			// (b) create map

	for(int i = 0 ; i < size ; i++)			// (c) initialize buckets
		this->map[i].front = NULL;
}

/*
 * Class Deconstructor
 *
 * Call the private member function freeHashMap()
 */

myHashMap::~myHashMap()
{
	freeHashMap();
}

/*
 * hashFunction()
 *
 * Input: Character pointer (to the key string)
 * 
 * Returns an index in the hashMap for the key/value pair.
 * Index is then used to specify which bucket the key/value pair will lie in.
 * The actual hash function itself is simple. It takes the sum of the unsigned integer values of 
 * characters, and takes the modulo of the size.
 * 
 */

uint32_t myHashMap::hashFunction(char *key)
{
	if(key == NULL)					// if key is NULL, function fails
		return -1;

	char *ptr = key;
	uint32_t index = 0	;			

	while(*ptr != '\0')				// iterate until end of string
	{
		index += (uint32_t) *ptr;
		ptr++;
	}

	return (index % this->size);
}

/*
 * set() stores the key/value pair in a Node attached to Bucket. 
 *
 * Input: (1) key string  (2) data object pointer/reference
 * Output: TRUE if function succeeds to add an entry
           FALSE is function fails to add an entry
 * 
 * Inserts key/value pair into the hashMap.
 *	 a. If duplicate is found OR capacity is reached, the function fails 
 *   b. Otherwise, function inserts the key/value entry 
 */

bool myHashMap::set(char *key, void *value)
{
	if(key == NULL){
		cout << "ERROR: Key must be a non-null value\n"; 
		return false;
	}

	if(this->count == this->size){
		cout << "ERROR: Capacity of hashMap is full\n";
		return false;
	}

	uint32_t index = this->hashFunction(key);				// retrieve the index 

	Bucket *currBucket = &(this->map[index]);				// bucket which entry is to be put in

	if( this->searchBucket(currBucket,key) ){				// check if key is already in the hashMap. 
		cout << "ERROR: Cannot insert a duplicate\n";
		return false;
	}

	/* It's not a duplicate, so it's safe to insert the key/value node entry to the hashMap */

	Node *temp = (Node *) malloc(sizeof(Node));				// dynamically allocate Node 

	uint32_t size = strlen(key);							// find the size of the key string

	temp->key = (char *) malloc(sizeof(char)*(size + 1));	// allocate enough space for the string, including null character

	strcpy(temp->key, key);									// copy string so entry can have its own copy
	temp->value = value;									// initialize value pointer

	temp->next = currBucket->front;							// adding Node entry to the linked list... 
	currBucket->front = temp;

	this->count++;											// increment count

	return true;
}

/*
 * get() : returns the value pointer associated with given key.
 *
 * Input: Key string
 * Output: Data object pointer/reference if function succeeds
 		   NULL if function fails (e.g If key is not found, then obviously there is no value, so a NULL pointer is returned)
 * 
 */

void* myHashMap::get(char *key)
{
	if(key == NULL)											// if key is null, function fails
		return NULL;

	uint32_t index = this->hashFunction(key);				// retrieve the index

	Bucket *currBucket = &(this->map[index]);				// bucket where entry SHOULD be located in (already)

	Node *ptr = currBucket->front;							// pointer to the beginning of currBucket's linked list

	while(ptr != NULL && ( strcmp(key, ptr->key) != 0 )){	// iterate until ptr is NULL or key is found!
		ptr = ptr->next;	
	}

	if(ptr == NULL)											// if pointer is null, function fails (key was not found)
		return NULL;


	return ptr->value;										// function succeeds, return the pointer to the data
}

/*
 * deleteit(): deletes a key/value entry from the hashMap 
 *
 * INPUT: Key string
 * OUTPUT: Returns the value associated with the key if key is found
 *		   If no key is found, NULL is returned
 *
 * NOTE: Only the dynamically allocated parts of the Node entry can be freed.
 *       The node, containing its fields, may be freed. But, the data value itself (pointed to by the data value void pointer) is not freed 
 *       because it was not dynamically allocated by the hashMap (it might not even be in the heap in the first place)
 *       
 */

void* myHashMap::deleteit(char *key)
{
	if(key == NULL)											// if key is null, function fails
		return NULL;

	uint32_t index = this->hashFunction(key);				// retrieve the index

	Bucket *currBucket = &(this->map[index]);				// bucket where entry SHOULD be located in (already)

	Node *ptr = currBucket->front;							// initialize pointers to travers linked list
	Node *prev = NULL;

	while(ptr != NULL && ( strcmp(key, ptr->key) != 0 )){	// iterate until ptr is NULL or key is found!
		prev = ptr;
		ptr = ptr->next;
	}

	if(ptr == NULL)							// CASE 1: if pointer is null, key was not found, function fails
		return NULL;


	if(prev == NULL){						// CASE 2: key is found in the first node in the linked list 

		currBucket->front = ptr->next;			// remove ptr from the linked list

	}else{									// CASE 3: all other cases

		prev->next = ptr->next;					// remove ptr from the linked list

	}

	void *var = ptr->value;				// store pointer of data/object for function return

	free(ptr->key);						// free dynamically allocated memory
	free(ptr);

	this->count--;						// decrement count


	return var;
}

/* 
 * load() returns the load factor of the hashMap. 
 */
float myHashMap::load(void)
{
	return  ( (double) count / (double) size );
}

/* PRIVATE MEMBER FUNCTIONS */


/*
 * searchBucket() searches the Bucket for a key
 * 
 * return true - if key is found
 * return false - if key is not found
 */
bool myHashMap::searchBucket(Bucket *currBucket, char *key)
{
	if(currBucket == NULL)		/* null pointer check (should not occur though since array was declared) */
		return false;;

	/*
	 * Initialize ptr TO front of linked list
	 * Initialize prev TO NULL
	 */
	Node * ptr = currBucket->front; 

	while(ptr != NULL && ( strcmp(key, ptr->key) != 0 )	){
		ptr = ptr->next;
	}

	/*
	 *	CASE 1: ptr == NULL , in which case the key was not found in the hashTable bucket
	 *  CASE 2: ptr != NULL , in which case the key is found
	 */

	 if(ptr == NULL){				/* Case 1 */
	 	return false;
	 }

	 								/* Case 2 */

	 return true;
}

/*
 * freeBucket() iterates through the linked list belonging to a Bucket and frees Nodes during its traversal
 */

void myHashMap::freeBucket(Node *currNode)
{

	Node * ptr = currNode;
	Node * prev;

	while(ptr != NULL){
		prev = ptr;
		ptr = ptr->next;
		free(prev->key);
		free(prev);
	}

	return;
}

/*
 * freeHashMap() 1) frees each individual bucket in the bucket array
 *				 2) frees the Bucket array itself
 */

void myHashMap::freeHashMap(void){

	for(int i = 0 ; i < this->size ; i++){
		
		if(this->map[i].front != NULL){
			
			freeBucket(this->map[i].front);
		}

	}

	delete this->map;
	
	return;
}

